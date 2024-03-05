
1. 功能说明：
此sample是爱芯SDK包提供的示例参考代码, 方便用户快速的理解如何使用Link机制建立VIN到IVPS的链路，通过IVPS分流后，送显示和送编码。
sample默认演示的是VIN --> IVPS --> VO --> VENC的完整pipeline，链路关系如下：

--------------------Link Table--------------------
         Src            |          Dst
(ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
--------------------------------------------------
(VIN        0       0) -> (IVPS     1       0)
(IVPS       1       0) -> (VO       0       0)
(IVPS       1       1) -> (VENC     0       1)
(IVPS       1       2) -> (VENC     0       2)


2. 使用示例：
查看help信息
/ # /opt/bin/sample_vin_ivps_vo_venc -h
Usage: /opt/bin/sample_vin_ivps_vo_venc -h for help

        -c: VIN Sensor Type
                0: Single DummySensor
                2: Single OS04A10

        -o: VO display interface resolution and VO device
                Interface: [dpi] [bt601] [bt656] [bt1120] [mipi]
                Resolution:
                        [576P50]        [480P60]        [720P50]        [720P60]
                        [800x480P60]    [1080P24]       [1080P25]       [1080P30]
                        [1080P50]       [1080P60]       [640x480P60]    [800x600P60]
                        [1024x768P60]   [1280x1024P60]  [1366x768P60]   [1440x900P60]
                        [1600x1200P60]  [1680x1050P60]  [1920x1200P60]  [2560x1600P60]
                        [3840x2160P24]  [3840x2160P25]  [3840x2160P30]  [3840x2160P50]
                        [3840x2160P60]  [4096x2160P24]  [4096x2160P25]  [4096x2160P30]
                        [4096x2160P50]  [4096x2160P60]  [720x1280P60]   [1080x1920P60]
                Device: [dev0] [dev1]

        -m(optional): Work Mode:
                0: LoadRaw Mode
                1: Sensor Mode
                2: TPG Mode

        -l(optional): Load raw node, only valid in ipc pipe now
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


举例一：dummySensor，DPI屏，800x480分辨率，运行命令如下：
/opt/bin/sample_vin_ivps_vo_venc -c 0 -o dpi@800x480P60@dev0


3. 运行结果：
通过cat  /proc/ax_proc/vin 观察VIN模块帧率是否正常。
通过cat  /proc/ax_proc/ivps 观察IVPS模块帧率是否正常。
通过cat  /proc/ax_proc/vo 观察VO模块各通道帧率是否正常。
通过cat  /proc/ax_proc/venc 观察VENC模块各通道帧率是否正常。

运行成功后，VO将在屏幕上显示数据流。
sample默认每个编码通道保存前30帧数据，生成的文件保存在当前执行命令的目录下，文件名为enc_0.264、enc_1.264、enc_2.264。


4. 注意事项：
     a) sample中缓存池并不是最优配置，仅供参考。在实际开发中，用户需要结合具体业务配置缓存池。
     b) VIN不再有分流能力，要想分流必须经过IVPS模块。
     c) 执行Ctrl + C 后需等一会才能退出sample。
     d) 在620Q上需要运行与axp sensor对应的sample命令。
     e) 在620Q上运行，需先根据显示信息修改dts屏显配置参数。
     f) 因为灌图需要申请额外的buffer，所以sample灌图暂时只支持DummySensor，如有灌图需求建议使用tuning-server,同时如果要在620Q上跑LoadRaw模式，需添加dummy_sensor的so库。