/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "ax_sys_api.h"
#include "ax_gzipd_api.h"

#define AX_GZIP_LOG_DBG printf
#define AX_GZIP_LOG_ERR printf
#define GZIPD_TILE_BLKSZ 4 * 16 *1024


struct timeval starttime, endtime;
void show_run_gzip_time(void) {
        gettimeofday(&endtime, 0);
        double time_us  = 1000000*(endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
        printf("\nrun gzipd took %d us\n", (int)time_us);
}

long getfilesize(FILE *pFile)
{
    if( pFile == NULL)
    {
        return -1;
    }

    long cur_pos = ftell(pFile);
    if(cur_pos == -1)
    {
        return -1;
    }

    if(fseek(pFile, 0L, SEEK_END) == -1)
    {
        return -1;
    }

    long size = ftell(pFile);

    if(fseek(pFile, cur_pos, SEEK_SET) == -1)
    {
        return -1;
    }

    return size;
}

static int _ax_gzipd_process_work(int handle, AX_GZIPD_IO_PARAM_T *ioParam)
{
    int ret;
    AX_U32 tile_cnt;
    AX_U32 last_tile_size = 0;
    AX_U64 tile_addr;
    AX_U64 totalSize;
    AX_U64 encodedDataAddr;
    AX_U64 tiles_addr_start;
    AX_U32 finishedDataLen;
    AX_GZIPD_RESULT_INFO_T result;

#ifdef AX_GZIPD_BYPASS_EN
    header_info.osize = header_info.isize;
#endif
    encodedDataAddr = ioParam->stInBuf.pPhyAddr;
    tile_addr = encodedDataAddr + sizeof(AX_GZIPD_HEADER_INFO_T);
    tile_cnt = ioParam->tilesNum;
    last_tile_size = ioParam->lastTileLen;

    printf("tile_cnt = %d, last_tile_size = %d\n", tile_cnt, last_tile_size);
    if (tile_cnt == 0) {
        if (AX_GZIPD_LastTileRun(handle, tile_addr, last_tile_size)) {
            printf(" run last tile error\n");
            return -1;
        }
        goto complete_finish;
    }

    tiles_addr_start = tile_addr;
    totalSize = ioParam->headerInfo.u32InSize - sizeof(AX_GZIPD_HEADER_INFO_T);
    ret = AX_GZIPD_TilesRun(handle, tiles_addr_start, totalSize, &finishedDataLen);
    printf("the size of output data is %d , ret = 0x%x\n", finishedDataLen, ret);
    if (ret == AX_GZIPD_PART_COMPLETE || ret == AX_GZIPD_STATUS_OK) {
    } else {
        printf("tile run fail ,ret = %d", ret);
        return -1;
    }

    if (totalSize > finishedDataLen) {
        tiles_addr_start += finishedDataLen;
        last_tile_size = totalSize - finishedDataLen;
        if (AX_GZIPD_LastTileRun(handle, tiles_addr_start, last_tile_size)) {
            AX_GZIP_LOG_ERR("lastly gzipd run last tile error\n");
            return -1;
        }
    }

complete_finish:
    ret = AX_GZIPD_WaitFinish(handle, &result);
    if (ret != AX_GZIPD_WORK_FINISH) {
        printf("GZIPD wait finish fail\n");
        return ret;
    }
    if (result.u32Result == AX_GZIPD_COMPLETE_SUCCESS) {
        printf("decompress the whole gzip file success \n");
        ret = 0;
    } else {
        printf("decompress the whole gzip file fail \n");
        ret = -1;
    }
    return ret;
}

int main(int argc, char **args)
{
    int ret;
    FILE *ifile;
    FILE *ofile;
    unsigned long sz_ifile;
    AX_GZIPD_IO_PARAM_T gzipd_param;
    AX_U32 handle;
    AX_GZIPD_HEADER_INFO_T headerinfo;

    if (argc < 2) {
        printf("usage: sample_gzipd -if ifile -of ofile \n");
        return -1;
    }

    char *in_file = args[2];
    char *out_file = args[4];

    if (in_file == NULL || out_file == NULL) {
        printf("input or output file error\n");
        return -1;
    }

    printf("input file[%s], output file[%s]\n", in_file, out_file);
    ifile = fopen(in_file, "rb");
    if (!ifile) {
        printf("open gziped file[%s] fail \n", in_file);
        return -1;
    }

    ofile = fopen(out_file, "wb");
    if (!ofile) {
        printf("open decompress file[%s] fail \n", out_file);
        return -1;
    }

    sz_ifile = getfilesize(ifile);
    if (sz_ifile < 0) {
        printf("get file size error : %ld\n", sz_ifile);
        return -1;
    }

    ret = AX_SYS_Init();
    if (ret != 0) {
        printf("AX_SYS_Init error, ret = %d\n",ret);
        return -1;
    }

    ret = AX_GZIPD_Init();
    if (ret) {
        printf("gzipd init fail\n");
        return -1;
    }

    ret = AX_SYS_MemAlloc(&gzipd_param.stInBuf.pPhyAddr,&gzipd_param.stInBuf.pVirAddr, sz_ifile, 64, (AX_S8 *)"gzip");
    if(ret != 0) {
        printf(" alloc cmm space to input file failed,ret = %d\n", ret);
        return -1;
    }

    ret = fread(gzipd_param.stInBuf.pVirAddr, 1, sz_ifile, ifile);
    if (ret < sz_ifile) {
        printf("fread input file fail,ret = %d, errno = %d\n", ret, errno);
    }

    ret = AX_GZIPD_CreateHandle(&handle, gzipd_param.stInBuf.pVirAddr, &headerinfo);
    if (ret) {
        printf("create gzipd handle fail, ret = 0x%x\n", ret);
        goto releae_res;
    }
    printf(" zip file header info ->cType=%c%c, BlkNum=0x%x, outsize=0x%x, Insize=0x%x, crc32=0x%x\n",
            headerinfo.cType[0],headerinfo.cType[1], headerinfo.u16BlkNum, headerinfo.u32OutSize, headerinfo.u32InSize, headerinfo.u32Crc32);

    ret = AX_SYS_MemAlloc(&gzipd_param.stOutBuf.pPhyAddr,&gzipd_param.stOutBuf.pVirAddr, headerinfo.u32OutSize, 64, (const AX_S8 *)"gzipd");
    if(ret != 0) {
        printf(" alloc cmm space to output file failed,ret = %d\n", ret);
        return -1;
    }

    memcpy(&gzipd_param.headerInfo, &headerinfo, sizeof(headerinfo));
    gzipd_param.u32TileSize = GZIPD_TILE_BLKSZ;
    ret = AX_GZIPD_Config(handle, &gzipd_param);

    gettimeofday(&starttime, 0);

    ret = _ax_gzipd_process_work(handle, &gzipd_param);
    if (ret) {
        printf("gzipd exec fail, ret = %d\n", ret);
        goto releae_res;
    }
    show_run_gzip_time();

    ret = fwrite(gzipd_param.stOutBuf.pVirAddr, 1, gzipd_param.headerInfo.u32OutSize, ofile);
    if (ret < gzipd_param.headerInfo.u32OutSize) {
        printf("fail to save decompress data to file, size =%d\n", ret);
    } else {
        printf("decompress success ,len = %d\n",ret);
    }

releae_res:
    AX_SYS_MemFree(gzipd_param.stOutBuf.pPhyAddr, gzipd_param.stOutBuf.pVirAddr);
    AX_SYS_MemFree(gzipd_param.stInBuf.pPhyAddr, gzipd_param.stInBuf.pVirAddr);
    AX_GZIPD_DestroyHandle(handle);
    fclose(ifile);
    fclose(ofile);
    AX_SYS_Deinit();
    AX_GZIPD_Deinit();
}