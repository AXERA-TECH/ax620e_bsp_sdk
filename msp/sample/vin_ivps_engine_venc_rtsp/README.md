
1. 功能说明：
此sample是爱芯SDK包提供的示例参考代码, 方便用户快速的理解如何使用Link机制建立VIN到IVPS，跑Yolov5s检测模型，再到VENC的链路，以及VENC后编码数据的RTSP推流。
此sample默认演示的是VIN --> IVPS --> AXEngine --> VENC -> RTSP的完整pipeline，链路关系如下：

--------------------Link Table--------------------
         Src            |          Dst
(ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
--------------------------------------------------
(VIN        0       0) -> (IVPS     1       0)
(IVPS       1       0) -> (VENC     0       0)
(IVPS       1       1) -> (VENC     0       1)
(IVPS       1       2) -> (VENC     0       2)


2. 使用示例：
查看help信息
/ # /opt/bin/sample_vin_ivps_engine_venc_rtsp -h
Usage:/opt/bin/sample_vin_ivps_engine_venc_rtsp -h for help

        -c: VIN Sample Case
                0: Single DummySensor
                1: Single OS04A10

        -m(optional): Work Mode
                0: LoadRaw Mode
                1: Sensor Mode
                2: TPG Mode

        -l(optional): load raw node, only valid in ipc pipe now
                0: ife node
                1: itp node
                2: rgb node
                3: yuv node

        -e(optional): SDR/HDR Mode
                1: SDR
                2: HDR 2DOL

        -a(optional): Enable AIISP
                0: Disable(default)
                1: Enable

        -d(optional): Continue Frame Dump
                n: N Frame Blk

        -r(optional): Enable RTSP
                0: Disable(default)
                1: Enable

举例一：OS04A10，SDR模式，RTSP推流，运行命令如下：
/opt/bin/sample_vin_ivps_engine_venc_rtsp -c 1 -m 1 -e 1 -r 1


3. 运行结果：
通过cat  /proc/ax_proc/vin 观察VIN模块帧率是否正常。
通过cat  /proc/ax_proc/ivps 观察IVPS模块帧率是否正常。
通过cat  /proc/ax_proc/venc 观察VENC模块各通道帧率是否正常。

此sample默认每个编码通道保存前30帧数据，生成的文件保存在当前执行命令的目录下，文件名为enc_0.264、enc_1.264、enc_2.264。


4. 注意事项：
     a) sample中缓存池并不是最优配置，仅供参考。在实际开发中，用户需要结合具体业务配置缓存池。
     b) VIN不再有分流能力，要想分流必须经过IVPS模块。
     c) 执行Ctrl + C 后需等一会才能退出sample。

