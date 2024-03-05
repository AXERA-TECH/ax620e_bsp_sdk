#!/bin/sh

cur_path=$(cd "$(dirname $0)";pwd)
cd $cur_path

echo "path:$cur_path"

process="sample_ivps"

pid=$(pidof ${process})
if [ $pid ]; then
  echo "${process} is already running, please check the process(pid: $pid) first."
  exit 1
fi

# ----------------------------------------------------------------------------------------------#
#
# settings
#
# ----------------------------------------------------------------------------------------------#

echo "ivps chip test start"

#echo 4 > /proc/sys/kernel/axprintk


# 1: CRITICAL
# 2: ERROR
# 3: WARNING
# 4: NOTICE  (default)
# 5: INFORMATION
# 6: VERBOSE
# 7: DATA
# export APP_LOG_LEVEL=3


# ----------------------------------------------------------------------------------------------#
#
#  launching
#
# ----------------------------------------------------------------------------------------------#

md5=`md5sum ${process} | awk '{ print $1 }'`
echo "lanuching ${process}, md5: ${md5} ..."

# input para
width=2688
height=1520
image_input=2688x1520.nv12
format=3 # 3:NV12

echo $1
if [ -z "$1" ]
then
	echo "0: test src width and height"
        echo "1: test dst width and height with one channel"
	exit
fi

if [ $1 -eq 0 ]
then
	read -p "pls input min of src width and  src height:" min_w min_h

	max_w=$width
	max_h=$height
	echo "min w:"$min_w
	echo "max w:"$max_w
	echo "min h:"$min_h
	echo "max h:"$max_h

	for i in $(seq $min_w 2 $max_w)
	do
		for j in $(seq $min_h 2 $max_h)
		do
			echo $i
			echo $j
			$cur_path/sample_ivps -v $cur_path/$image_input@${format}@${max_w}x${max_h}@${i}x${j} -n 1
		done
	done
else
        read -p "pls input min and max of dst width:" min_w max_w
	read -p "pls input min and max of dst height:" min_h max_h

	if [ -z "$max_w" ]
	then
		echo "max_w is null"
		max_w=$min_w
        fi
	if [ -z "$max_h" ]
        then
		echo "max_h is null"
                max_h=$min_h
        fi
        echo "min w:"$min_w
        echo "max w:"$max_w
        echo "min h:"$min_h
        echo "max h:"$max_h

        for i in $(seq $min_w 2 $max_w)
        do
                for j in $(seq $min_h 2 $max_h)
                do
                        echo $i
                        echo $j
                        $cur_path/sample_ivps -v $cur_path/$image_input@${format}@${width}x${height}@${width}x${height} -n 1 --ch ${i}x${j}
                done
        done
fi


#$cur_path/sample_ivps -v $cur_path/2688x1520.nv12@3@2688x1520@${max_w}x${max_h} -n 1


