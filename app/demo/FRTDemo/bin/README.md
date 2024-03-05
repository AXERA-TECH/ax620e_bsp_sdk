#FRTDemo

## 如何执行？
### 执行IPC Pipeline
1. cd /opt/bin/FRTDemo
2. （可选）vi config/ipc/ppl.json 配置pipeline上前后两级模块对应关系。
3. （可选）vi config/ipc/ivps.json 配置IVPS模块参数。
4. （可选）vi config/ipc/encoder.json 配置编码通道参数。
5. （可选）vi config/ipc/options.ini 配置运行时各功能参数，包括RTSP/WEB缓存帧buff大小，OSD/板端录像等功能开关。[参数说明](#配置参数)
6. 执行./run.sh -p 0 -s 1 -n 2 [参数说明](#启动参数)
>   添加-d用于gdb调试，内部使用了SIGUSR2信号作为定时器，因此gdb调试时输入**handle SIGUSR2 nostop noprint**忽略SIGUSR2信号。

### 执行IPC Pipeline (待实现)
1. cd /opt/bin/FRTDemo
2. 执行./run.sh -p 1 -s 1 [参数说明](#启动参数)

## 如何编译？
1. cd app/demo/FRTDemo
2. make p=xxx clean
3. make p=xxx
4. make p=xxx install
> p=xxx 指定编译项目名，示例：make p=AX630C_emmc_arm64_k419

## 如何预览？
1. RTSP流预览：可通过第三方工具，比如VLC，输入RTSP流地址（参照终端打印输出：“Play the stream using url: <<<<< rtsp://IP:8554/axstream0 >>>>>”）进行预览。
1. WEB预览：可通过Chrome打开网页（参照终端打印输出：“Preview the video using URL: <<<<< http://IP:8080 >>>>>”）进行预览。

# <a href="#启动参数">启动参数</a>
p: pipeline index, indicates ppl load type, like IPC or Pano etc.
   0: IPC pipeline (DEFAULT)
   1: Pano pipeline
s: sensor type.
   0: OS04A10 (DEFAULT)
   1: SC450AI
   2: IMX678
n: scenario, indicates the scenario to load, which is always defined in config files.
   0: default (DEFAULT: Dual sensor)
   1: Single sensor
l: log level, indicates the log level.
   ALERT = 1, CRITICAL = 2, ERROR = 3 (DEFAULT), WARN = 4, NOTICE = 5, INFO = 6, DEBUG = 7, DATA = 8
t: log target, indicates the log output targets.
   SYSLOG = 1, APPLOG = 2, STDOUT = 4 (DEFAULT) (Calculate the sum if multiple targets is required)
d: start with gdb for debugging, value **NOT REQUIRED**
u: testsuite type.
   0: Dual default
   1: Single default

# <a href="#配置参数">配置参数</a>

|   #   |          参数         |    参数范围   |       说明                        |
| ----- | --------------------- | ------------ | ---------------------------------|
|   1   | RTSPMaxFrmSize        | [0 - 8000000]| 单位：B                           |
|   2   | WebVencFrmSizeRatio   |              | Web缓存帧相对YUV的size比例         |
|   3   | WebJencFrmSizeRatio   |              | Web缓存帧相对YUV的size比例         |
|   4   | PrintFPS              |              | 0：不打印 1:打印                   |
|   5   | EnableOSD             |              | 0：关闭OSD 1:开启OSD               |
|   6   | EnableMp4Record       |              | 0：关闭板端录像 1:开启板端录像      |
|   7   | MP4RecordSavedPath    |              | 板端录像保存路径                   |
