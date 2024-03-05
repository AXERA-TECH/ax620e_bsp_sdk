
1. 功能说明：
此sample是爱芯SDK包提供的示例参考代码, 方便用户快速的理解如何使用Link机制建立IVPS到VENC的链路。
此sample默认演示的是 IVPS --> VENC 的完整pipeline，链路关系如下：

--------------------Link Table--------------------
         Src            |          Dst
(ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
--------------------------------------------------
(IVPS       1       0) -> (VENC     0       0)
(IVPS       1       1) -> (VENC     0       1)


2. 使用示例：
查看help信息
/ # /opt/bin/sample_ivps_venc
Usage:/opt/bin/sample_ivps_venc for help

举例一： Process the source image (1920x1080 NV12 format).
/opt/bin/sample_ivps_venc -w 1920 -h 1080 -W 1920 -H 1080 -m 0 -b 2048 -B 2048 -f 25 -q 10 -Q 51 -p 10 -P 51 -R 40 -r 30 -i 1920x1080@420p.yuv

3. 运行结果：
通过cat  /proc/ax_proc/ivps 观察IVPS模块配置是否正常。
通过cat  /proc/ax_proc/venc 观察VENC模块各通道信息是否正常。

此sample默认每个编码通道保存编码数据，生成的文件保存在当前执行命令的目录下，文件名为enc_0.264、enc_1.265。


4. 注意事项：
     a) sample中缓存池并不是最优配置，仅供参考。在实际开发中，用户需要结合具体业务配置缓存池。
     b) 执行Ctrl + C 后需等一会才能退出sample。
     c) 不支持旋转功能。

