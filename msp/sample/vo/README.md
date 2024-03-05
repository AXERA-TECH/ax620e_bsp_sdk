
1）功能说明：
vo文件夹下面的代码, 是爱芯SDK包提供的示例参考代码, 方便客户快速的理解VO整个模块的配置流程.
示例代码演示的是如下的功能：VO模块初始化、Layer/Chn的使用、以及图像的显示./opt/etc/vo.ini
用于演示功能的配置集。


2）使用示例：
A. 通过DPI输出分辨率为800x480 60Hz的彩条, 运行命令如下：
   sample_vo -d 0

   -d: layer+display 参数0是指/opt/etc/vo.ini配置文件中[case0]下的配置参数, 详见vo.ini文件

B. 只layer处理，运行命令如下：
   sample_vo -l 7

   -l：只layer处理，不显示。参数7是指/opt/etc/vo.ini配置文件中[case7]下的配置参数

C. VO连续播放显示，使用vo.ini配置文件中case3的配置，加载/mnt/vo/1920x1080_cheliangdaolu2_30fps_300f_NV12.yuv
   连续文件进行播放，运行命令如下：
   sample_vo -p 3

   -p：播放显示，参数10是指/opt/etc/vo.ini配置文件中[case3]下的配置参数，[case3]配置下的参数
    chn_file_name = /mnt/vo/1920x1080_cheliangdaolu2_30fps_300f_NV12.yuv 指定加载的播放文件。

D. 枚举显示设备支持的分辨率，运行命令如下：
   sample_vo -e 0

   -e：指定要枚举的设备，目前只能是0或1

3） 注意事项：
   在620Q上屏显配置默认关闭，-p -d -e case不能运行。如需屏显功能，请先根据显示信息修改dts屏显配置参数。
