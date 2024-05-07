#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ax_isp_common.h"
#include "ax_sys_api.h"
#include "common_hw.h"
#include "common_sys.h"


/* TODO user need config device node number */
AX_S8 COMMON_ISP_GetI2cDevNode(AX_U8 nDevId)
{
    switch (AX_SYS_GetChipType()) {
    case AX620Q_CHIP:
            return 0;
    break;
    case AX630C_CHIP:
        if (nDevId == 0)
            return 0;
        else
            return 2;
    break;
    default:
        if (nDevId == 0)
            return 0;
        else
            return 2;
    break;
    }
}
