#!/bin/sh

if [ $# -eq 0 ]; then
    mode="-i"
else
    mode=$1
fi

function load_nfs()
{
    echo "loading nfs ko ..."
    insmod /soc/ko/sunrpc.ko
    insmod /soc/ko/grace.ko
    insmod /soc/ko/lockd.ko
    insmod /soc/ko/nfs.ko
    insmod /soc/ko/nfsv2.ko
    insmod /soc/ko/nfsv3.ko
    echo "load nfs ko Done!!!"
}

function remove_nfs()
{
    echo "removing nfs ko ..."
    rmmod nfsv3
    rmmod nfsv2
    rmmod nfs
    rmmod lockd
    rmmod grace
    rmmod sunrpc
    echo "remove nfs Done!!!"
}

function nfs()
{
    if [ "$mode" == "-i" ]; then
        load_nfs
    elif [ "$mode" == "-r" ]; then
        remove_nfs
    else
        echo "[error] Invalid param, please use the following parameters"
        echo "-i:  insmod"
        echo "-r:  rmmod"
    fi
}

nfs
