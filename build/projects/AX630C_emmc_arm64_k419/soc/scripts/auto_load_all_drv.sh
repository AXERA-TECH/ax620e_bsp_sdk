#!/bin/sh

if [ $# -eq 0 ]; then
    mode="-i"
else
    mode=$1
fi

function load_drv()
{
    echo "run auto_load_all_drv.sh start "
    insmod /soc/ko/ax_sys.ko
    insmod /soc/ko/ax_cmm.ko cmmpool=anonymous,0,0x80000000,1024M
    insmod /soc/ko/ax_pool.ko
    insmod /soc/ko/ax_base.ko
    insmod /soc/ko/ax_npu.ko
    insmod /soc/ko/ax_vo.ko
    insmod /soc/ko/ax_fb.ko
    insmod /soc/ko/ax_ivps.ko
    insmod /soc/ko/ax_vpp.ko
    insmod /soc/ko/ax_gdc.ko
    insmod /soc/ko/ax_tdp.ko
    insmod /soc/ko/ax_venc.ko
    insmod /soc/ko/ax_jenc.ko
    insmod /soc/ko/ax_vdec.ko
    insmod /soc/ko/ax_mipi_rx.ko
    insmod /soc/ko/ax_proton.ko
    insmod /soc/ko/ax_audio.ko
    insmod /soc/ko/ax_ddr_dfs.ko
    insmod /soc/ko/ax_ive.ko
    insmod /soc/ko/ax_avs.ko

    echo "run auto_load_all_drv.sh end "
}

function remove_drv()
{
    rmmod ax_avs
    rmmod ax_ive
    rmmod ax_ddr_dfs
    rmmod ax_audio
    rmmod ax_proton
    rmmod ax_mipi_rx
    rmmod ax_vdec
    rmmod ax_jenc
    rmmod ax_venc
    rmmod ax_tdp
    rmmod ax_gdc
    rmmod ax_vpp
    rmmod ax_ivps
    rmmod ax_fb
    rmmod ax_vo
    rmmod ax_npu
    rmmod ax_base
    rmmod ax_pool
    rmmod ax_cmm
    rmmod ax_sys
}

function auto_drv()
{
    if [ "$mode" == "-i" ]; then
        load_drv
    elif [ "$mode" == "-r" ]; then
        remove_drv
    else
        echo "[error] Invalid param, please use the following parameters:"
        echo "-i:  insmod"
        echo "-r:  rmmod"
    fi
}

auto_drv

exit 0
