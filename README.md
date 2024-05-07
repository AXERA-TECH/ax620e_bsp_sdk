# ax620e_bsp_sdk

## What is this?

This is a ax620e linux bsp sdk form AX620e_SDK_V1.7.0_P2. currently it is application layer open source.

## Which target support

- AX630C
- AX620Q

## How to compile

### prepare arm gcc

```
wget http://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabihf/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz
sudo tar -xvf gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf.tar.xz -C /opt/
export PATH="/opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/:$PATH"
````

### prepare compile files

```
git clone https://github.com/AXERA-TECH/ax620q_bsp_sdk.git
cd ax620q_bsp_sdk
```

Download the third-party zip file and decompress it into third-party dir

- [百度网盘](https://pan.baidu.com/s/1BPvwQ3a93f5BRh3kdVUjWQ?pwd=g6nu)
- [GoogleDrive](https://drive.google.com/)(待补充)

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
ls msp/out/arm_glibc/bin/
FRTDemo         sample_cipher_s  sample_gzipd_s  sample_ivps               sample_npu_classification    sample_rtc       sample_vdec              sample_venc                       sample_vin_ivps_vo_venc
sample_audio    sample_cmm       sample_isp_3a   sample_ivps_jenc_slice    sample_npu_classification_s  sample_rtc_s     sample_vdec_ivps_venc    sample_venc_s                     sample_vin_s
sample_audio_s  sample_cmm_s     sample_ive      sample_ivps_jenc_slice_s  sample_npu_yolov5s           sample_skel      sample_vdec_ivps_venc_s  sample_vin                        sample_vo
sample_avs      sample_dma       sample_ive_s    sample_ivps_s             sample_npu_yolov5s_s         sample_skel_s    sample_vdec_ivps_vo      sample_vin_ivps_skel_venc_rtsp    sample_vo_s
sample_avs_s    sample_dma_s     sample_ives     sample_ivps_venc          sample_pool                  sample_sysmap    sample_vdec_ivps_vo_s    sample_vin_ivps_skel_venc_rtsp_s
sample_cipher   sample_gzipd     sample_ives_s   sample_ivps_venc_s        sample_pool_s                sample_sysmap_s  sample_vdec_s            sample_vin_ivps_venc_rtsp
```
