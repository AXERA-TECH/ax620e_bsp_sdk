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
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ax_base_type.h>
#include <ax_efuse_api.h>

#define TEST_BLK_START1 0
#define TEST_BLK_END1 63

int main(void)
{
    AX_S32 i;
    AX_S32 ret;
    AX_S32 data;

    ret = AX_EFUSE_Init();
    if (ret != 0) {
        printf("Efuse init failed %x\n", ret);
        return -1;
    }
    for (i = TEST_BLK_START1; i < TEST_BLK_END1; i++) {
        ret = AX_EFUSE_Read(i, &data);
        if (ret != 0) {
            printf("efuse test read error %x, %x\n", i, ret);
            return -1;
        }
        printf("##[AXERA-ASLT]CASE_DATA:EFUSE:block%02d = 0x%08x\n", i, data);
    }

    ret = AX_EFUSE_Deinit();
    if (ret != 0) {
        printf("Efuse Deinit failed %x\n", ret);
        return -1;
    }
    printf("Efuse test PASS!\n");
    return 0;
}
