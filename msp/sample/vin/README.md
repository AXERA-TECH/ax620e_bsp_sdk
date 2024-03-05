
1）功能说明：
vin文件夹下面的代码, 是爱芯SDK包提供的示例参考代码, 方便客户快速的理解VIN整个模块的配置流程.
示例代码演示的是如下的pipeline形态：单摄、单摄AI-ISP、双摄双4M、双摄AI-ISP.
我司目前仅提供demo板适配的sensor的初始化配置: OV-OS04A10，如有需要可以按照下文的第4点“加入新sensor步骤”


2）使用示例：
单摄单路OS04A10 4M的sensor, 跑一路SDR, 运行命令如下：
./sample_vin -c 1 -m 1 -e 1 [-d N]

-c： 选择不同的场景:
                    0-TPG(DummySensor)
                    1-单摄OS04A10
                    2-双摄OS04A10
                    3-单摄SC450AI
                    4-双摄SC450AI
                    5-Double OS04A10 + BT656
                    6-Single S5KJN1SQ03
                    7-Single OS04A10 DCG HDR
                    8-Single OS04A10 DCG VS HDR
                    20-Single DVP
                    21-Single BT.601
                    22-Single BT.656
                    23-Single BT.1120
                    24-Single LVDS

-m:  选择不同的模式:
                    0-LoadRaw 模式
                    1-sensor 模式
                    2-tpg模式

-a:  选择使能AIISP模式:
                    0-关闭AIISP（未配置-a时默认关闭）
                    1-使能AIISP

-e:  选择SDR/HDR模式:
                    1-SDR (默认运行SDR)
                    2-HDR 2DOL

-d:  连续dump时需要申请的blk个数， N-新增N个Frame缓存

3）注意事项：
（1）common pool内存块如何申请？我司提供了一个内存配置表（详见sample_vin.c文件中的定义）,
	 用户可根据自己的业务,在此处配置整个系统各个模块的buf,这样的设计更有利于理解和使用.
 (2) -d选项一般不用添加，如果需要连续dump，则需要加上此选项，后面跟一个帧buffer的个数，如./sample_vin -c 1 -d 100
 (3) 在620Q上需要运行与axp sensor对应的sample命令
 (4) 因为灌图需要申请额外的buffer，所以sample灌图暂时只支持DummySensor，如有灌图需求建议使用tuning-server,同时如果要在620Q上跑LoadRaw模式，需添加dummy_sensor的so库。
 (5) 运行DCG VS HDR会做两次pipeline切换动作, 每次切换DCG路会做SDR/HDR切换，VS路在切换过程中不断流。

4）加入新sensor支持步骤,详细的代码修改参见文档《20 - AX Sensor 调试指南.docx》
（1）配置Sensor对应的common pool
（2）配置Sensor、VIN、Chn的参数
（3）注册Sensor库
（4）common子函数中添加对应的Sensor Case
