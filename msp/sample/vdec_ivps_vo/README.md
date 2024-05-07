1）功能说明：
该模块是爱芯SDK包提供的解码、IVPS、VO性能消耗的demo示例代码，方便客户快速理解和掌握视频解码相关接口的使用。
代码演示了如下功能：解码模块初始化、解码Send线程解析和发送码流、IVPS/VENC模块初始化、各模块退出功能。
编译后得到可执行程序sample_vdec_ivps_vo, 位于/opt/bin目录，可用于VDEC link IVPS，IVPS link vo 功能验证。
该模块解码仅在帧模式下支持，其余模式未做支持。


2）参数说明：
-i:  输入码流路径。
-T：解码类型；26：jpegdec； 96：h264 vdec；
-L: 解码循环次数;默认1
--res： 设置码流分辨率，默认典型分辨率是1920x1920。用于配置vdec宽高属性，配置是必须的。
--enDisplayMode：0=预览模式，1=反压模式
--waitTime: 用例执行时长，默认20s
--voRes:输出分辨率, def 14: AX_VO_OUTPUT_800x480_60(类型定义可以查看头文件ax_vo_api.h)，用于配置ivps, vo宽高属性，配置是必须的。
--voType:输出类型, def 0: AX_VO_INTF_DPI (类型定义可以查看头文件ax_vo_api.h)

使用示例：
查看help信息:
/opt/bin/sample_vdec_ivps_vo

H264协议：
./sample_vdec_ivps_vo --res=1280x720 --enDisplayMode 0 -T 96 -i nba_1280x720.h264 --voRes 14 --voType 0

jpeg:
./sample_vdec_ivps_vo --res=1920x1080 --enDisplayMode 0 -T 26 -i  1920x1080_60frm.mjpg

3） 注意事项：
   该case默认不能在620Q上运行，如需验证，请先根据显示信息修改dts屏显配置参数。
