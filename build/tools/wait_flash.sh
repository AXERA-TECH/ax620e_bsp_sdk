#!/bin/bash

OUT_FSTAB_FILE=$1
OUT_RCS_FILE=$2

sed_cmd=":a;/done/!{N;ba};s#while \[ ! -e /dev/mmcblk0p.*done#while "

partition=`grep -E "^ */dev/mmcblk" ${OUT_FSTAB_FILE} | grep -Eo "/dev/mmcblk.*"`
OLD_IFS=$IFS
IFS=$'\n'
for line in $partition; do
    dev=`echo $line | awk '{print $1}'`
    part=`echo $dev | awk '{print $2}'`
    sed_cmd=${sed_cmd}"[ ! -e $dev ] ||\n\t"
done
IFS=$OLD_IFS
sed_cmd="${sed_cmd::-7}"
sed_cmd=${sed_cmd}"; do\n\t:\ndone#"
# echo $sed_cmd

sed -i "$sed_cmd" ${OUT_RCS_FILE}
