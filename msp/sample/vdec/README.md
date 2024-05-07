1）功能说明：
该模块是爱芯SDK包提供的视频解码单元示例代码，方便客户快速理解和掌握视频解码相关接口的使用。
代码演示了如下功能：解码模块初始化、解码Send线程解析和发送码流、解码Get线程获取和保存YUV数据、解码模块去初始化。
编译后得到可执行程序sample_vdec,位于/opt/bin目录，可用于视频解码功能验证。

-i: 输入码流路径。
-c：解码通道数；默认为 1。
-T：解码类型；26：jpegdec； 96：h264 vdec； 265: h265 vdec。
-w：是否将解码后的YUV保存到文件， 0：不保存； 1：保存。
-L：循环解码次数，默认为 1次。
-M: 发送码流模式；0：按NAL方式发送码流，每次发送以一个NAL为单位（暂不支持）；
                1：帧发送模式，每次发送以一帧为单位；
                2: SLICE发送模式，每次发送一个SLICE（暂不支持）；
                3：流发送模式，每次发送不定长度码流（JPEG/MJPEG不支持）；
                4：兼容发送模式，一帧码流可分多次发送，当一帧码流发送完毕时 bEndOfFrame 需置为 AX_TRUE（暂不支持）；
-s：发送码流模式为流发送模式有效，每次流发送长度，值大于0小于等于输入buffer长度有效，sample中buffer长度为3MBytes,该值默认值为10kBytes。
--res： 设置输出分辨率，默认典型分辨率是1920x1920。
--select 1：call AX_VDEC_SelectGrp（默认）；0：disable

2）使用示例：
举例一：查看help信息
/opt/bin/sample_vdec  -h

举例二: 解码1080p jpeg，并将解码后的yuv保存到当前目录
/opt/bin/sample_vdec -i /opt/data/vdec/1080P_qp9.jpg -T 26 -w 1 --res=1920x1080

举例三：解码1080p h264，并将解码后的yuv保存到当前目录
/opt/bin/sample_vdec -i /opt/data/vdec/1080p.h264 -T 96 -w 1 --res=1920x1080

举例四: 单帧解码接口解码1080p jpeg，并将解码后的yuv保存到当前目录
/opt/bin/sample_vdec -i /opt/data/vdec/1080P_qp9.jpg -T 26 -w 1 --res=1920x1080 -j 1

3）运行结果：
运行成功后，在当前目录应生成解码后的yuv数据，名称示例:group0_1920_1080.yuv，用户可打开看实际效果。

4）Sample Log 开关：
echo 8 7 > /proc/ax_proc/logctl         # 允许 DEBUG LOG 输出； 具体 LEVEL 参看 ax_global_type.h 中的枚举类型 AX_LOG_LEVEL_E

5）AX SDK Vdec Log开关：
echo 8 7 > /proc/ax_proc/logctl         # 允许 DEBUG LOG 输出； 具体 LEVEL 参看 ax_global_type.h 中的枚举类型 AX_LOG_LEVEL_E
