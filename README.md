# ax620e_bsp_sdk

## What is this?

This is a ax620e linux bsp sdk based on official version AX620e_SDK_V2.0.0_P7 and changed for M5Stack's products. currently it is application layer open source.

## Which target support

- AX630C
- AX620Q

## How to compile

### prepare arm gcc

#### AX630C


```
wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz
sudo tar -xvf gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz -C /opt/
export PATH="/opt/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/:$PATH"
````

#### AX620Q

Please get it from [here](https://github.com/AXERA-TECH/ax620q_bsp_sdk/releases/download/v2.0.0/arm-AX620E-linux-uclibcgnueabihf_V3_20240320.tgz)

```
sudo tar -zxvf arm-AX620E-linux-uclibcgnueabihf_V3_20240320.tgz -C /opt/
export PATH="/opt/arm-AX620E-linux-uclibcgnueabihf/bin/:$PATH"
```

### prepare compile files

```
git clone -b m5stack https://github.com/AXERA-TECH/ax620e_bsp_sdk.git
cd ax620e_bsp_sdk
```

Download the third-party zip file and decompress it into third-party dir

- [百度网盘](https://pan.baidu.com/s/1BPvwQ3a93f5BRh3kdVUjWQ?pwd=g6nu)
- [Google Drive](https://drive.google.com/drive/folders/1JkZQlCtPz2U3W0mvBwwryHXW_Uo79stI?usp=sharing)

```
$ tree -L 2
.
├── LICENSE
├── README.md
├── app
│   ├── Makefile
│   ├── component
│   └── demo
├── build
│   ├── Makefile
│   ├── axp_make.sh
│   ├── color.mk
│   ├── config.mak
│   ├── cross_arm_glibc.mak
│   ├── krules.mak
│   ├── out
│   ├── project.mak
│   ├── projects
│   ├── rules.mak
│   ├── tools
│   └── version.mak
├── msp
│   ├── Makefile
│   ├── component
│   ├── out
│   └── sample
└── third-party
    ├── Makefile
    ├── cmdline
    ├── drm
    ├── faac
    ├── fdk-aac
    ├── libsamplerate
    ├── live
    ├── mp4
    ├── opencv-4.5.5
    ├── openssl
    ├── opus
    ├── swupdate
    └── tinyalsa
```

### compile app and samples

#### AX630C 

compile app demo
```
cd app
make p=AX630C_emmc_arm64_k419 isntall
```

compile sample
```
cd msp/sample
make p=AX630C_emmc_arm64_k419 isntall
```

the result 
```
ls msp/out/arm64_glibc/bin/
FRTDemo         sample_cipher_s  sample_gzipd_s  sample_ivps               sample_npu_classification    sample_rtc       sample_vdec              sample_venc                       sample_vin_ivps_vo_venc
sample_audio    sample_cmm       sample_isp_3a   sample_ivps_jenc_slice    sample_npu_classification_s  sample_rtc_s     sample_vdec_ivps_venc    sample_venc_s                     sample_vin_s
sample_audio_s  sample_cmm_s     sample_ive      sample_ivps_jenc_slice_s  sample_npu_yolov5s           sample_skel      sample_vdec_ivps_venc_s  sample_vin                        sample_vo
sample_avs      sample_dma       sample_ive_s    sample_ivps_s             sample_npu_yolov5s_s         sample_skel_s    sample_vdec_ivps_vo      sample_vin_ivps_skel_venc_rtsp    sample_vo_s
sample_avs_s    sample_dma_s     sample_ives     sample_ivps_venc          sample_pool                  sample_sysmap    sample_vdec_ivps_vo_s    sample_vin_ivps_skel_venc_rtsp_s
sample_cipher   sample_gzipd     sample_ives_s   sample_ivps_venc_s        sample_pool_s                sample_sysmap_s  sample_vdec_s            sample_vin_ivps_venc_rtsp
```

#### AX620Q

compile app demo
```
cd app
make p=AX620Q_nand_arm32_k419 install
```

compile sample
```
cd msp/sample
make p=AX620Q_nand_arm32_k419 install
```

the result 
```
ls msp/out/arm_uclibc/bin/
FRTDemo         sample_cipher_s  sample_gzipd_s  sample_ivps               sample_npu_classification    sample_rtc       sample_vdec              sample_venc                       sample_vin_ivps_vo_venc
sample_audio    sample_cmm       sample_isp_3a   sample_ivps_jenc_slice    sample_npu_classification_s  sample_rtc_s     sample_vdec_ivps_venc    sample_venc_s                     sample_vin_s
sample_audio_s  sample_cmm_s     sample_ive      sample_ivps_jenc_slice_s  sample_npu_yolov5s           sample_skel      sample_vdec_ivps_venc_s  sample_vin                        sample_vo
sample_avs      sample_dma       sample_ive_s    sample_ivps_s             sample_npu_yolov5s_s         sample_skel_s    sample_vdec_ivps_vo      sample_vin_ivps_skel_venc_rtsp    sample_vo_s
sample_avs_s    sample_dma_s     sample_ives     sample_ivps_venc          sample_pool                  sample_sysmap    sample_vdec_ivps_vo_s    sample_vin_ivps_skel_venc_rtsp_s
sample_cipher   sample_gzipd     sample_ives_s   sample_ivps_venc_s        sample_pool_s                sample_sysmap_s  sample_vdec_s            sample_vin_ivps_venc_rtsp
```