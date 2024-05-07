1）功能说明：
该模块是爱芯SDK包提供的解码、IVPS、编码性能消耗的demo示例代码，方便客户快速理解和掌握视频解码相关接口的使用。
代码演示了如下功能：解码模块初始化、解码Send线程解析和发送码流、IVPS/VENC模块初始化、各模块退出功能。
编译后得到可执行程序sample_vdec_ivps_venc, 位于/opt/bin目录，可用于VDEC->IVPS->VENC、VDEC->VENC功能验证。
该模块解码仅在帧模式下支持，其余模式未做支持。

2）参数说明：
-i:  输入码流路径。
-T：解码类型；26：jpegdec； 96：h264 vdec；
-L: 解码循环次数;默认1
--res： 设置输出分辨率，默认典型分辨率是1920x1920。用于配置vdec、ivps、venc宽高属性，配置是必须的。
--enDisplayMode：0=预览模式，1=反压模式(VENC不支持反压模式，故该模块仅支持预览模式)
--waitTime: 用例执行时长，默认20s
--bOpenIvps：是否串联IVPS模块，0：否   1：是，默认0
--sWriteFrames：是否将编码输出写入文件， 0： 否  1：是，默认0

使用示例：
查看help信息:
/opt/bin/sample_vdec_ivps_venc

H264协议：
./sample_vdec_ivps_venc --res=1920x1080 --waitTime 5 --enDisplayMode 0 -T 96 --bOpenIvps 0 -i  res_1920_1080_svc.264

jpeg:
./sample_vdec_ivps_venc --res=1920x1080 --waitTime 5 --enDisplayMode 0 -T 26 --bOpenIvps 0 -i  1920x1080_60frm.mjpg

