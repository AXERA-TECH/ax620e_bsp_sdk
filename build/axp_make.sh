#!/bin/sh

set -e

echo "making axp ..."

while getopts "o:p:s:d:v:z:a:l:f:" arg
do
	case "$arg" in
		o)
			echo "support optee: $OPTARG"
			SUPPORT_OPTEE=$OPTARG
			;;
		f)
			FLASH_PARTITIONS=$OPTARG
			;;
		p)
			echo "project: $OPTARG"
			PROJECT=$OPTARG
			;;
		s)
			echo "sensor type: $OPTARG"
			SENSOR_TYPE=$OPTARG
			;;
		d)
			echo "detect type: $OPTARG"
			DETECT_TYPE=$OPTARG
			;;
		v)
			echo "sdk version: $OPTARG"
			VERSION=$OPTARG
			;;
		z)
			echo "enable gzip: $OPTARG"
			GZIPD_ENABLE=$OPTARG
			;;
		a)
			echo "enable ab part: $OPTARG"
			AX_SUPPORT_AB_PART=$OPTARG
			;;
		l)
			echo "libc type: $OPTARG"
			LIBC_TYPE=$OPTARG
			;;
	esac
done

CHIP_NAME=${PROJECT%\_*}
CHIP_GROUP=${CHIP_NAME:0:6}
VERSION_EXT=${VERSION}_$(date "+%Y%m%d%H%M%S")

echo "CHIP_GROUP: $CHIP_GROUP"

if [ -z "$SENSOR_TYPE" ]; then
AXP_NAME=${PROJECT}_${VERSION_EXT}_${LIBC_TYPE}.axp
AXP_UBUNTU_ROOTFS_NAME=${PROJECT}_ubuntu_rootfs_${VERSION_EXT}_${LIBC_TYPE}.axp
else
if [ -z "$DETECT_TYPE" ]; then
SENSOR_TYPE=$(echo $SENSOR_TYPE | tr ' ' '_')
AXP_NAME=${PROJECT}_${SENSOR_TYPE}_${VERSION_EXT}_${LIBC_TYPE}.axp
AXP_UBUNTU_ROOTFS_NAME=${PROJECT}_ubuntu_rootfs_${SENSOR_TYPE}_${VERSION_EXT}_${LIBC_TYPE}.axp
else
DETECT_TYPE=$(echo $DETECT_TYPE | tr ' ' '_')
SENSOR_TYPE=$(echo $SENSOR_TYPE | tr ' ' '_')
AXP_NAME=${PROJECT}_${SENSOR_TYPE}_${DETECT_TYPE}_${VERSION_EXT}_${LIBC_TYPE}.axp
AXP_UBUNTU_ROOTFS_NAME=${PROJECT}_ubuntu_rootfs_${SENSOR_TYPE}_${DETECT_TYPE}_${VERSION_EXT}_${LIBC_TYPE}.axp
fi
fi

LOCAL_PATH=$(pwd)
HOME_PATH=$LOCAL_PATH/..
OUTPUT_PATH=$LOCAL_PATH/out
IMG_PATH=$OUTPUT_PATH/$PROJECT/images
AXP_PATH=$OUTPUT_PATH/$AXP_NAME
AXP_UBUNTU_ROOTFS_PATH=$OUTPUT_PATH/$AXP_UBUNTU_ROOTFS_NAME
cp $HOME_PATH/build/tools/imgsign/eip_ax620e.bin $IMG_PATH/eip_ax620e.bin
TOOL_PATH=$HOME_PATH/tools/mkaxp/make_axp_v2.py
GEN_XML_PATH=$HOME_PATH/build/tools/gen_axp_xml.py
PAC_XML_PATH=$HOME_PATH/build/out/$PROJECT/images/$PROJECT.xml
PROJECT_MAK=$HOME_PATH/build/projects/$PROJECT/project.mak
TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml

DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
DTB_A_PATH=$IMG_PATH/${PROJECT}_signed.dtb
DTB_B_PATH=$IMG_PATH/${PROJECT}_signed.dtb
EIP_PATH=$IMG_PATH/eip_ax620e.bin
FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
FDL2_PATH=$IMG_PATH/fdl2_signed.bin
SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
ATF_PATH=$IMG_PATH/atf_bl31_signed.bin
ATF_A_PATH=$IMG_PATH/atf_bl31_signed.bin
ATF_B_PATH=$IMG_PATH/atf_b_bl31_signed.bin
UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
UBOOT_A_PATH=$IMG_PATH/u-boot_signed.bin
UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
UBUNTU_ROOTFS_PATH=$IMG_PATH/ubuntu_rootfs_sparse.ext4
PARAM_PATH=$IMG_PATH/param_sparse.ext4
SOC_PATH=$IMG_PATH/soc_sparse.ext4
OPT_PATH=$IMG_PATH/opt_sparse.ext4
OPT_2_PATH=$IMG_PATH/opt_2_sparse.ext4
KERNEL_PATH=$IMG_PATH/boot_signed.bin
KERNEL_A_PATH=$IMG_PATH/boot_signed.bin
KERNEL_B_PATH=$IMG_PATH/boot_signed.bin
LOGO_PATH=$IMG_PATH/axera_logo.bmp
LOGO_A_PATH=$IMG_PATH/axera_logo.bmp
LOGO_B_PATH=$IMG_PATH/axera_logo.bmp
RISCV_PATH=$IMG_PATH/rtthread_signed.bin
RECOVERY_PATH=$IMG_PATH/recovery_signed.bin
CUSTOMER_PATH=$IMG_PATH/customer.img
MODEL_PATH=$IMG_PATH/model.img
if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
OPTEE_PATH=$IMG_PATH/optee_signed.bin
OPTEE_A_PATH=$IMG_PATH/optee_signed.bin
OPTEE_B_PATH=$IMG_PATH/optee_signed.bin
SD_PACK_OPTEE=true
else
SD_PACK_OPTEE=false
fi

if [ ! "$AX_SUPPORT_AB_PART" = "FALSE" ]; then
	SD_UPDATE_PARM=" -ab yes "
fi

AXP_PARM_DEFAULT="EIP=$EIP_PATH FDL1=$FDL1_PATH FDL2=$FDL2_PATH"
get_axp_parm() {
	AXP_PARM=" $AXP_PARM_DEFAULT "
	uppercase=$(echo $1 | tr '[:lower:]' '[:upper:]')
	partitions=$(echo $uppercase | sed 's/[^()]*\(([^)]*)\)[^,]*/\1/g')
	partitions=$(echo $partitions | sed 's/[()]/ /g')
	for oneopt in $partitions; do
		oneopt_path=${oneopt}_PATH
		if [ ! -z ${!oneopt_path} ]; then
			AXP_PARM+="$oneopt=${!oneopt_path} "
		fi
	done
}

python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH

if [[ "$PROJECT" =~ "AX630C_nand" ]] || [[ "$PROJECT" =~ "AX620Q_nand" ]]; then
	PARAM_PATH=$IMG_PATH/param.ubi
	ROOTFS_PATH=$IMG_PATH/rootfs_soc_opt.ubi
elif [[ "$PROJECT" =~ "AX620Q_nor" ]]; then
	ROOTFS_PATH=$IMG_PATH/rootfs.img
	OPT_PATH=$IMG_PATH/opt.img
elif [[ "$PROJECT" =~ "AX620Q_fastnor" ]]; then
	ROOTFS_PATH=$IMG_PATH/rootfs.img
elif [[ "$PROJECT" =~ "AX620Q_fastnand_arm32_k419" ]]; then
	ROOTFS_PATH=$IMG_PATH/rootfs.img
	CUSTOMER_PATH=$IMG_PATH/customer.ubi
elif [[ "$PROJECT" =~ "AX630C_fastemmc" ]]; then
	CUSTOMER_PATH=$IMG_PATH/customer_sparse.ext4
elif [[ "$PROJECT" =~ "AX630C_emmc" ]] ;then
	:
else
	echo "make axp failed"
fi

get_axp_parm "$FLASH_PARTITIONS"
python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH ${AXP_PARM}
if [ -f $UBUNTU_ROOTFS_PATH ]; then
	ROOTFS_PATH=$UBUNTU_ROOTFS_PATH
	get_axp_parm "$FLASH_PARTITIONS"
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH ${AXP_PARM}
fi
python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee $SD_PACK_OPTEE ${SD_UPDATE_PARM}
python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee $SD_PACK_OPTEE ${SD_UPDATE_PARM}
