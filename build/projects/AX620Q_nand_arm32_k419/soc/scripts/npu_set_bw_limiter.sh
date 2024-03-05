#!/bin/sh

echo "run npu_set_bw_limiter.sh start "

if [ "$(ls /proc/ax_proc/bw_limit | grep npu)" = "" ]; then
    cd /proc/ax_proc/bw_limit
    echo 14 1 > register
else
    echo "already register bw limit for NPU"
fi

chip_type=$(cat /proc/ax_proc/chip_type)

echo "this chip type is $chip_type"

devmem 0x3890068 32 0x1
devmem 0x3890064 32 0x1

if [ "$chip_type" == "AX620V200_CHIP" ] || [ "$chip_type" == "AX630C_CHIP" ]; then
    echo 3000 > /proc/ax_proc/bw_limit/npu/limiter_val_sum_rdwr
else
    echo 2000 > /proc/ax_proc/bw_limit/npu/limiter_val_sum_rdwr
fi

echo "run npu_set_bw_limiter.sh end "
