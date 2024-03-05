#!/bin/sh

set -e

echo "making axp ..."

while getopts "o:p:s:v:z:a:" arg
do
    case "$arg" in
        o)
            echo "support optee: $OPTARG"
            SUPPORT_OPTEE=$OPTARG
            ;;
        p)
            echo "project: $OPTARG"
            PROJECT=$OPTARG
            ;;
        s)
            echo "sensor type: $OPTARG"
            SENSOR_TYPE=$OPTARG
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
    esac
done

CHIP_NAME=${PROJECT%\_*}
CHIP_GROUP=${CHIP_NAME:0:6}
VERSION_EXT=${VERSION}_$(date "+%Y%m%d%H%M%S")

echo "CHIP_GROUP: $CHIP_GROUP"

if [ -z "$SENSOR_TYPE" ]; then
AXP_NAME=${PROJECT}_${VERSION_EXT}.axp
AXP_UBUNTU_ROOTFS_NAME=${PROJECT}_ubuntu_rootfs_${VERSION_EXT}.axp
else
SENSOR_TYPE=$(echo $SENSOR_TYPE | tr ' ' '_')
AXP_NAME=${PROJECT}_${SENSOR_TYPE}_${VERSION_EXT}.axp
AXP_UBUNTU_ROOTFS_NAME=${PROJECT}_ubuntu_rootfs_${SENSOR_TYPE}_${VERSION_EXT}.axp
fi

LOCAL_PATH=$(pwd)
HOME_PATH=$LOCAL_PATH/..
OUTPUT_PATH=$LOCAL_PATH/out
IMG_PATH=$OUTPUT_PATH/$PROJECT/images
AXP_PATH=$OUTPUT_PATH/$AXP_NAME
AXP_UBUNTU_ROOTFS_PATH=$OUTPUT_PATH/$AXP_UBUNTU_ROOTFS_NAME
cp $HOME_PATH/build/tools/imgsign/eip_ax620e.bin $IMG_PATH/eip_ax620e.bin
TOOL_PATH=$HOME_PATH/tools/mkaxp/make_axp.py
GEN_XML_PATH=$HOME_PATH/build/tools/gen_axp_xml.py
PAC_XML_PATH=$HOME_PATH/build/out/$PROJECT/images/$PROJECT.xml
PROJECT_MAK=$HOME_PATH/build/projects/$PROJECT/project.mak

if [ "$PROJECT" = "AX630C_emmc_arm64_k515" ] || [ "$PROJECT" = "AX630C_emmc_arm64_k419" ]; then
if [ ! "$AX_SUPPORT_AB_PART" = "FALSE" ]; then
	DTB_A_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	DTB_B_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	ATF_A_PATH=$IMG_PATH/atf_bl31_signed.bin
	ATF_B_PATH=$IMG_PATH/atf_b_bl31_signed.bin
	UBOOT_A_PATH=$IMG_PATH/u-boot_signed.bin
	UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
	UBUNTU_ROOTFS_PATH=$IMG_PATH/ubuntu_rootfs_sparse.ext4
	PARAM_PATH=$IMG_PATH/param_sparse.ext4
	SOC_PATH=$IMG_PATH/soc_sparse.ext4
	OPT_PATH=$IMG_PATH/opt_sparse.ext4
	BOOT_A_PATH=$IMG_PATH/boot_signed.bin
	BOOT_B_PATH=$IMG_PATH/boot_signed.bin
	LOGO_A_PATH=$IMG_PATH/axera_logo.bmp
	LOGO_B_PATH=$IMG_PATH/axera_logo.bmp
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	OPTEE_A_PATH=$IMG_PATH/optee_signed.bin
	OPTEE_B_PATH=$IMG_PATH/optee_signed.bin
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}_optee_ab.xml
	SD_PACK_OPTEE=true
	else
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}_ab.xml
	SD_PACK_OPTEE=false
	fi
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_A_PATH $ATF_B_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $OPTEE_A_PATH $OPTEE_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_A_PATH $ATF_B_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $OPTEE_A_PATH $OPTEE_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	else
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_A_PATH $ATF_B_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_A_PATH $ATF_B_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	fi
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee $SD_PACK_OPTEE -ab yes
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee $SD_PACK_OPTEE
else
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	ATF_PATH=$IMG_PATH/atf_bl31_signed.bin
	ATF_B_PATH=$IMG_PATH/atf_b_bl31_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
	UBUNTU_ROOTFS_PATH=$IMG_PATH/ubuntu_rootfs_sparse.ext4
	PARAM_PATH=$IMG_PATH/param_sparse.ext4
	SOC_PATH=$IMG_PATH/soc_sparse.ext4
	OPT_PATH=$IMG_PATH/opt_sparse.ext4
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	LOGO_PATH=$IMG_PATH/axera_logo.bmp
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}_optee.xml
	OPTEE_PATH=$IMG_PATH/optee_signed.bin
	SD_PACK_OPTEE=true
	else
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	SD_PACK_OPTEE=false
	fi
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $ATF_B_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $OPTEE_PATH $DTB_PATH $BOOT_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $ATF_B_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $OPTEE_PATH $DTB_PATH $BOOT_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	else
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $ATF_B_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $DTB_PATH $BOOT_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $ATF_B_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $DTB_PATH $BOOT_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	fi
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee $SD_PACK_OPTEE
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee $SD_PACK_OPTEE
fi
elif [ "$PROJECT" = "AX630C_emmc_arm32_k419" ]; then
if [ ! "$AX_SUPPORT_AB_PART" = "FALSE" ]; then
	DTB_A_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	DTB_B_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	UBOOT_A_PATH=$IMG_PATH/u-boot_signed.bin
	UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
	UBUNTU_ROOTFS_PATH=$IMG_PATH/ubuntu_rootfs_sparse.ext4
	PARAM_PATH=$IMG_PATH/param_sparse.ext4
	SOC_PATH=$IMG_PATH/soc_sparse.ext4
	OPT_PATH=$IMG_PATH/opt_sparse.ext4
	BOOT_A_PATH=$IMG_PATH/boot_signed.bin
	BOOT_B_PATH=$IMG_PATH/boot_signed.bin
	LOGO_A_PATH=$IMG_PATH/axera_logo.bmp
	LOGO_B_PATH=$IMG_PATH/axera_logo.bmp
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	OPTEE_A_PATH=$IMG_PATH/optee_signed.bin
	OPTEE_B_PATH=$IMG_PATH/optee_signed.bin
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}_optee_ab.xml
	SD_PACK_OPTEE=true
	else
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}_ab.xml
	SD_PACK_OPTEE=false
	fi
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $OPTEE_A_PATH $OPTEE_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $OPTEE_A_PATH $OPTEE_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	else
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_A_PATH $UBOOT_B_PATH $LOGO_A_PATH $LOGO_B_PATH $DTB_A_PATH $DTB_B_PATH $BOOT_A_PATH $BOOT_B_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	fi
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee $SD_PACK_OPTEE -ab yes
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee $SD_PACK_OPTEE
else
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
	UBUNTU_ROOTFS_PATH=$IMG_PATH/ubuntu_rootfs_sparse.ext4
	PARAM_PATH=$IMG_PATH/param_sparse.ext4
	SOC_PATH=$IMG_PATH/soc_sparse.ext4
	OPT_PATH=$IMG_PATH/opt_sparse.ext4
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	LOGO_PATH=$IMG_PATH/axera_logo.bmp
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}_optee.xml
	OPTEE_PATH=$IMG_PATH/optee_signed.bin
	SD_PACK_OPTEE=true
	else
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	SD_PACK_OPTEE=false
	fi
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	if [ ! "$SUPPORT_OPTEE" = "FALSE" ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $OPTEE_PATH $DTB_PATH $BOOT_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $OPTEE_PATH $DTB_PATH $BOOT_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	else
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $DTB_PATH $BOOT_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	if [ -f $UBUNTU_ROOTFS_PATH ]; then
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_UBUNTU_ROOTFS_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $DTB_PATH $BOOT_PATH $UBUNTU_ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	fi
	fi
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee $SD_PACK_OPTEE
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee $SD_PACK_OPTEE
fi
elif [ "$PROJECT" = "AX630C_nand_arm64_k515" ] || [ "$PROJECT" = "AX630C_nand_arm64_k419" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	ATF_PATH=$IMG_PATH/atf_bl31_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	PARAM_PATH=$IMG_PATH/param.ubi
	KERNEL_PATH=$IMG_PATH/boot_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_soc_opt.ubi
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	echo "make boot.img 2 file..."
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $UBOOT_PATH $PARAM_PATH $DTB_PATH $KERNEL_PATH $ROOTFS_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
elif [ "$PROJECT" = "AX620Q_nand_arm32_k419" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	PARAM_PATH=$IMG_PATH/param.ubi
	KERNEL_PATH=$IMG_PATH/boot_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_soc_opt.ubi
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	echo "make boot.img 2 file..."
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $PARAM_PATH $DTB_PATH $KERNEL_PATH $ROOTFS_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
elif [ "$PROJECT" = "AX620Q_nor_arm32_k419" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	KERNEL_PATH=$IMG_PATH/boot_signed.bin
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	ROOTFS_PATH=$IMG_PATH/rootfs.img
	CUSTOMER_PATH=$IMG_PATH/customer.img
	OPT_PATH=$IMG_PATH/opt.img
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	echo "make boot.img 2 file..."
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $UBOOT_PATH $DTB_PATH $KERNEL_PATH $ROOTFS_PATH $CUSTOMER_PATH $OPT_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
elif [ "$PROJECT" = "AX620Q_nor_arm64_k515" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	ATF_PATH=$IMG_PATH/atf_bl31_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	KERNEL_PATH=$IMG_PATH/boot_signed.bin
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	ROOTFS_PATH=$IMG_PATH/rootfs.img
	CUSTOMER_PATH=$IMG_PATH/customer.img
	OPT_PATH=$IMG_PATH/opt.img
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	echo "make boot.img 2 file..."
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $ATF_PATH $UBOOT_PATH $DTB_PATH $KERNEL_PATH $ROOTFS_PATH $CUSTOMER_PATH $OPT_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
elif [ "$PROJECT" = "AX620Q_fastnor_arm32_k419" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	KERNEL_PATH=$IMG_PATH/boot_signed.bin
	RISCV_PATH=$IMG_PATH/rtthread_signed.bin
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	ROOTFS_PATH=$IMG_PATH/rootfs.img
	RECOVERY_PATH=$IMG_PATH/recovery_signed.bin
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	CUSTOMER_PATH=$IMG_PATH/customer.img
	echo "make boot.img 2 file..."
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $DTB_PATH $KERNEL_PATH $RISCV_PATH $ROOTFS_PATH $CUSTOMER_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
elif [ "$PROJECT" = "AX620Q_fastnor_arm64_k515" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	ATF_PATH=$IMG_PATH/atf_bl31_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	KERNEL_PATH=$IMG_PATH/boot_signed.bin
	RISCV_PATH=$IMG_PATH/rtthread_signed.bin
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	ROOTFS_PATH=$IMG_PATH/rootfs.img
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	CUSTOMER_PATH=$IMG_PATH/customer.img
	echo "make boot.img 2 file..."
	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $UBOOT_PATH $DTB_PATH $KERNEL_PATH $RISCV_PATH $ROOTFS_PATH $CUSTOMER_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
elif [ "$PROJECT" = "AX630C_fastemmc_arm64_k515" ] || [ "$PROJECT" = "AX630C_fastemmc_arm64_k419" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	ATF_PATH=$IMG_PATH/atf_bl31_signed.bin
	ATF_B_PATH=$IMG_PATH/atf_b_bl31_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
	PARAM_PATH=$IMG_PATH/param_sparse.ext4
	SOC_PATH=$IMG_PATH/soc_sparse.ext4
	OPT_PATH=$IMG_PATH/opt_sparse.ext4
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	LOGO_PATH=$IMG_PATH/axera_logo.bmp
	RISCV_PATH=$IMG_PATH/rtthread_signed.bin

	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $ATF_PATH $ATF_B_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $DTB_PATH $BOOT_PATH $RISCV_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee false
elif [ "$PROJECT" = "AX630C_fastemmc_arm32_k419" ]; then
	TEMPLATE_XML_PATH=$HOME_PATH/build/projects/${PROJECT}/${PROJECT}.xml
	DTB_PATH=$IMG_PATH/${PROJECT}_signed.dtb
	EIP_PATH=$IMG_PATH/eip_ax620e.bin
	FDL1_PATH=$IMG_PATH/fdl_${PROJECT}_signed.bin
	FDL2_PATH=$IMG_PATH/fdl2_signed.bin
	SPL_PATH=$IMG_PATH/spl_${PROJECT}_signed.bin
	DDRINIT_PATH=$IMG_PATH/ddrinit_${PROJECT}_signed.bin
	UBOOT_PATH=$IMG_PATH/u-boot_signed.bin
	UBOOT_B_PATH=$IMG_PATH/u-boot_b_signed.bin
	ROOTFS_PATH=$IMG_PATH/rootfs_sparse.ext4
	PARAM_PATH=$IMG_PATH/param_sparse.ext4
	SOC_PATH=$IMG_PATH/soc_sparse.ext4
	OPT_PATH=$IMG_PATH/opt_sparse.ext4
	BOOT_PATH=$IMG_PATH/boot_signed.bin
	LOGO_PATH=$IMG_PATH/axera_logo.bmp
	RISCV_PATH=$IMG_PATH/rtthread_signed.bin

	python3 $GEN_XML_PATH $PROJECT $TEMPLATE_XML_PATH $PROJECT_MAK $PAC_XML_PATH
	python3 $TOOL_PATH -p $CHIP_GROUP -v $VERSION_EXT -x $PAC_XML_PATH -o $AXP_PATH $EIP_PATH $FDL1_PATH $FDL2_PATH $DDRINIT_PATH $UBOOT_PATH $UBOOT_B_PATH $LOGO_PATH $DTB_PATH $BOOT_PATH $RISCV_PATH $ROOTFS_PATH $PARAM_PATH $SOC_PATH $OPT_PATH $SPL_PATH
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_update -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH  -optee false
	python3 $HOME_PATH/build/tools/sd_upgrade_pack.py -type sd_boot -path $HOME_PATH/build/out/$PROJECT/images -xml $PAC_XML_PATH -optee false
else
	echo "make axp failed"
fi
