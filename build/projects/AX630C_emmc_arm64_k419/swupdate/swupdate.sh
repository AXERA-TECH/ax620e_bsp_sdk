#!/bin/sh

export PATH=$PATH:/opt/swupdate/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/swupdate/lib

help_function() {
	echo -e "\e[33m"
	echo " URL:	    ./swupdate -u 10.126.12.107:8000/AX620E_demo_ota.swu"
	echo "Local:	    ./swupdate -i /mnt/AX620E_demo_ota.swu"
	echo "URL&Crypto:   ./swupdate -k /opt/swupdate/public.pem -u 10.126.12.107:8000/AX620E_demo_ota.swu"
	echo -e "\e[0m"
}

function get_env() {
	fw_printenv | grep ${1}= | awk -F = '{ print $2 }'
}

while getopts "u:i:k:h" opt; do
	case $opt in
		u )
			OTA_OPT="-d"
			OTA_PARM="-u ${OPTARG}"
			;;
		i )
			OTA_OPT="-i"
			OTA_PARM="${OPTARG}"
			;;
		k )
			CRYPTO_OPT="-k"
			CRYPTO_PARM="${OPTARG}"
			;;
		h )
			help_function
			exit
			;;
		\? )
			help_function
			exit
			;;
	esac
done


if [ -z "$OTA_PARM" ]; then
	help_function
	exit 1
fi

bootsystem=`get_env "bootsystem"`

if [ "$bootsystem" = "A" ]; then
	echo "start ota update system B"
	selection="-e stable,copy2"
else
	echo "start ota update system A"
	selection="-e stable,copy1"
fi

swupdate ${selection} -f /etc/swupdate.cfg ${CRYPTO_OPT} ${CRYPTO_PARM} ${OTA_OPT} "${OTA_PARM}" -v
