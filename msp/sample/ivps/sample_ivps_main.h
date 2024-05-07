/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_IVPS_MAIN_H_
#define _SAMPLE_IVPS_MAIN_H_

#include "ivps_util.h"
#include "ivps_help.h"
#include "ivps_parser.h"
#include "sample_ivps_pipeline.h"
#include "sample_ivps_region.h"
#include "sample_ivps_dewarp.h"
#include "sample_ivps_sync_api.h"

typedef enum
{
    IVPS_LINK_NULL,
    IVPS_LINK_IVPS,
    IVPS_LINK_VENC,
    IVPS_LINK_JENC,
    IVPS_LINK_BUTT
} IVPS_LINK_T;

typedef struct
{
    IVPS_ARG_T tIvpsArg;
    pthread_t change_tid;
    pthread_t region_tid;
    pthread_t send_frame_tid;
    pthread_t get_frame_tid;

    AX_S32 nIvpsRepeatNum;
    AX_S32 nIvpsStreamNum;
    AX_S32 nIvpsGetNum;
} SAMPLE_IVPS_MAIN_T;

/* From ivps_parser.c */
int IVPS_ArgsParser(int argc, char *argv[], IVPS_ARG_T *ptArg);
int IVPS_ChangeIniParser(const char *ininame, SAMPLE_IVPS_CHANGE_T *pChangeCfg);
int IVPS_GrpIniParser(const char *ininame, SAMPLE_IVPS_GRP_T *pGrpCfg);
int IVPS_ChnInfoParser(const IVPS_ARG_T *ptArg, AX_IVPS_PIPELINE_ATTR_T *ptPpl);
int IVPS_DewarpIniParser(const char *ininame, SAMPLE_IVPS_DEWARP_T *pDewarpCfg);
int IVPS_DewarpIniParserType(const char *ininame);

/* From sample_ivps_pipeline.c */
AX_S32 IVPS_StartGrp(const IVPS_ARG_T *ptArg, SAMPLE_IVPS_GRP_T *pGrp);
AX_S32 IVPS_StopGrp(const SAMPLE_IVPS_GRP_T *pGrp);
AX_S32 IVPS_GrpThreadStart(AX_VOID *src, AX_VOID *dst);
AX_S32 IVPS_GrpThreadStop(AX_VOID);
AX_S32 IVPS_AttrChangeThreadStart(const IVPS_ARG_T *ptArg, SAMPLE_IVPS_GRP_T *pGrp, AX_S32 nChangeIdx);
AX_S32 IVPS_AttrChangeThreadStop(AX_VOID);

/* From sample_ivps_region.c */
AX_S32 IVPS_StartRegion(AX_U32 nRegionNum);
AX_S32 IVPS_StopRegion(AX_VOID);
AX_S32 IVPS_StopRegionById(AX_S32 nRegionId);
AX_S32 IVPS_RegionUpdateThreadStart(AX_S32 nRegionNum, SAMPLE_IVPS_GRP_T *pGrp, AX_BOOL bStopTest);
AX_S32 IVPS_RegionUpdateThreadStop(AX_BOOL bStopTest);

/* From sample_ivps_link.c */
AX_S32 SAMPLE_IVPS_LinkIvps(const IVPS_ARG_T *ptArg, AX_S32 nGrpIdx, AX_S32 nChnIdx, SAMPLE_IVPS_GRP_T *pGrp);

/* From sample_ivps_sync_api.c */
AX_S32 SAMPLE_IVPS_Dewarp(const IVPS_ARG_T *ptArg, const SAMPLE_IVPS_GRP_T *pGrp);

/* From sample_ivps_sync_api.c */
AX_S32 SAMPLE_IVPS_SyncApi(const IVPS_ARG_T *ptArg, const SAMPLE_IVPS_GRP_T *pGrp, SAMPLE_IVPS_SYNC_API_T *ptSyncIntf);
AX_S32 SAMPLE_IVPS_SyncApiRegion(const IVPS_ARG_T *ptArg, const SAMPLE_IVPS_GRP_T *pGrp,
                                 const SAMPLE_IVPS_REGION_T *ptRegion);


extern SAMPLE_IVPS_GRP_T gSampleIvpsGrp;
extern SAMPLE_IVPS_GRP_T gSampleIvpsGrpExt;
extern SAMPLE_IVPS_MAIN_T gSampleIvpsMain;
#endif /* _SAMPLE_IVPS_MAIN_H_ */
