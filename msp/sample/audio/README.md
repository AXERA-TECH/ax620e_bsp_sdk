sample_audio

1）功能说明：
audio文件夹下面的代码, 是爱芯SDK包提供的示例参考代码, 方便客户快速的理解audio整个模块的配置流程.
示例代码演示的是如下的功能：ai录音、ao播放、ai_aenc编码、adec_ao解码.
我司提供everest厂家的codec驱动: es8388、es7210、es8311、es7243l和es8156


2）使用示例：
举例一：查看help信息
sample_audio -h

举例二：录制16kHz音频
sample_audio ai -D 0 -d 0 -r 16000 -p 160 -w 1

举例三：启用FIXED模式回声消除录制16kHz音频
sample_audio ai -D 0 -d 0 -r 16000 -p 160 --aec-mode 2 --routing-mode 0 --layout 1 -w 1

举例四：播放16kHz音频
sample_audio ao -D 0 -d 1 -r 16000

举例五：录制16kHz音频并且编码
sample_audio ai_aenc -D 0 -d 0 -r 16000 -p 160 -w 1

举例六：录制16kHz音频并且单声道编码
sample_audio ai_aenc -D 0 -d 0 -r 16000 -p 160 --layout 1 --aenc-chns 1 -w 1

举例七：解码并且播放16kHz音频
sample_audio adec_ao -D 0 -d 1 -r 16000

举例八：内置codec 上行HPF LPF EQ
sample_audio ai -D 0- d 0 --hpf 1 --hpf-freq 200 --hpf-db -12 --lpf 1 --lpf-freq 3000 --lpf-db 0 --eq 1

举例九：内置codec 下行HPF LPF EQ
sample_audio ao -D 0 -d 1 --hpf 1 --hpf-freq 200 --hpf-db -12 --lpf 1 --lpf-freq 3000 --lpf-db 0 --eq 1

3）示例运行结果：
运行成功后，执行Ctrl+C退出，在当前目录应生成wave文件，用户可打开看实际效果。

4）注意事项：
（1）声卡号和设备号，请参考/dev/snd/，举例说明:
   pcmC0D0c: card 0, device 0, capture device
   pcmC0D1p: card 0, device 1, playback device