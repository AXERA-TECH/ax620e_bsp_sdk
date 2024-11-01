1) 功能说明：

该模块是UVC（USB Video Class）示例代码。

支持os04a10和sc450ai sensor：
输出分辨率为360p，540p，720p，1080p，2688x1520，帧率为30的MJPEG/H264/H265格式的视频流;
输出分辨率为360p@30fps，480p@30fps, 540p@20fps，720p@10fps，1080p@5fps YUY2格式的视频流。

支持dummy sensor:
输出分辨率为720p,帧率为30的MJPG格式的视频流，通过读取固定JPG格式图片数据来充当sensor数据，非真实sensor数据；
输出分辨率360p帧率为30，分辨率480p帧率为30，分辨率540p帧率为20，分辨率720p帧率为10，分辨率1080p帧率为5的
YUY2格式的视频流，通过绘制色彩条图片数据来充当sensor数据，非真实sensor数据，故称为dummy sensor。

PC端调试UVC Camera可以使用PotPlayer播放器，该播放器支持视频录制，截图，旋转等。

2) 板端文件
可执行文件在板端/opt/bin/sample_uvc目录下
uvc-gadget-composite.sh： uvc驱动设置脚本
sample_uvc： sample 可执行程序

资源文件通常在/opt/data/uvc/目录下，如果没有（比如AX620E_nor工程），则需要自己准备同样分辨率的图片放到板端，位置只要可读即可。
1280x720.jpg： 用于dummy sensor输出mjpeg格式的固定图片数据

3) 参数说明

./uvc-gadget-composite.sh <1> <2> <3> <4> <5>
参数1: start or stop
参数2: usb2 is supported
参数3: uvc device count, support 2 devices at maximum
参数4: 0: os04a10 sensor, 1: dummy sensor, 2: sc450ai sensor
参数5: 0: iso mode，1: bulk mode

./sample_uvc -n <number> -y <sns> -a <flag>
-n: v4l2 buffer个数, 默认4个
-y: sensor类型
-a: 使能aiisp：1，开启；0，关闭，默认开启AIISP
-b: 使能bulk模式
-h: 打印help

4) 使用示例

示例一： OS04A10 Sensor 单摄

cd /opt/bin/sample_uvc
./uvc-gadget-composite.sh start usb2 1 0 0
./sample_uvc -y 0


示例二： dummy Sensor 单摄，图片文件的路径可以自行修改。

cd /opt/bin/sample_uvc
./uvc-gadget-composite.sh start usb2 1 1 0
./sample_uvc -y 2 -i /opt/data/uvc/1280x720.jpg


sample_uvc执行起来后，在PC端通过potplayer选择UVC Camera打开预览。

4) PotPlayer播放器操作说明：
在网上下载一个PotPlayer软件安装包，安装在PC上。在PC上打开PotPlayer视频播放器,Alt+D快捷键打开
摄像头选项卡，在设备一栏中选择UVC Camera或者USB Video Device（可尝试检索更新按钮更新设备状态）。

对于os04a10 sensor在格式一栏中选择:
MJPG/H264/H265（640x360，960x540，1280x720，1920x1080，2688x1520）格式；
YUY2(640x360, 640x480, 960x540, 1280x720, 1920x1080)格式；
然后点击打开设备按钮，即可打开UVC Camera

对于dummy sensor在格式一栏中选择:
MJPEG（1280x720）格式，
YUY2(640x360,640x480,960x540,1280x720,1920x1080)格式。
然后点击打开设备按钮，即可打开UVC Camera

在Potplayer播放器主界面左上角，点击下拉菜单“PotPlayer ∨”，选择“视频”功能，在子菜单中根据需要选择
“图像处理”，“视频录制”，“图像截取”等功能，实现图像处理、视频录制、截图保存功能。