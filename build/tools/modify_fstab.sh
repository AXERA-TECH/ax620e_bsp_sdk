filename=$1
flash_partitions=$2

#Remove the last comma and space
flash_partitions=$(echo "$flash_partitions" | sed 's/[,\ ]*$//')
#Get the number of partitions
flash_partitions_num=`echo ${flash_partitions} | tr ',' '\n' | wc -l`
#Get the number of partitions in fstab that need to be mounted
fstab_dev_num=`grep -E "^ */dev/mtdblock[0-9]{1,3}|^ */dev/mmcblk[0-9]p[0-9]{1,3}" $filename | wc -l`
#Calculate the mount starting point in fstab
start_position=$((flash_partitions_num - fstab_dev_num + 1))

change_fs_type() {
    old_line=`grep $1 ${filename}`
    new_line=`grep $1 ${filename} | sed "s/ext2\|ext4\|jffs2\|squashfs/$2/"`
    sed -i "s#$old_line#$new_line#" $filename
}

#Parse the fs type parameter
parse_fs_type_para() {
    if [ $# -lt 2 ]; then
        return 0
    fi
    num_args=$#
    for ((i=1; i<=num_args; i+=2));do
        arg1=${!i}
        eval arg2="\${$((i+1))}"
        arg2=${arg2,,}
        tmp=`echo $arg2 | grep -E "ext2|ext4|jffs2|squashfs"`
        if [ -z "$tmp" ];then
            continue
        fi
        change_fs_type ${arg1} ${arg2}
    done
}

parse_fs_type_para "${@:3}"

while IFS= read -r line
do
    #Get the line starting with /dev/mtdblock|/dev/mmcblk[0-9]p and get the matching value
    # dev_position=`echo "$line" | grep -Eo "^ */dev/mtdblock[0-9]{1,3}|^ */dev/mmcblk[0-9]p[0-9]{1,3}"`
    dev_position=`echo "$line" | grep -Eo "^ */dev/mtdblock[0-9]{1,3}|^ */dev/mmcblk[0-9]p[0-9]{1,3}"`
    if [ -n "$dev_position" ]; then
        fstab_dev=`echo "$dev_position" | grep -Eo "/dev/mtdblock|/dev/mmcblk[0-9]p"`
        partition=$(echo "$line" | sed -e 's/^[ \t]*//' | tr -s '[:blank:]' ',' | cut -d',' -f2 | tr -d '/')
        partition_position=$(echo "$flash_partitions" | tr ',' '\n' | grep -n "($partition)" | cut -d ':' -f 1)
        if [ -n "$partition_position" ]; then
            new_dev_position="${fstab_dev}${partition_position}"
        else
            new_dev_position="${fstab_dev}${start_position}"
            start_position=$((start_position + 1))
        fi
        #new mount point
        new_line=`echo "$line" | sed "s#${dev_position}#${new_dev_position}#"`
        sed -i "s#$line#$new_line#" $filename
    fi
done < "$filename"