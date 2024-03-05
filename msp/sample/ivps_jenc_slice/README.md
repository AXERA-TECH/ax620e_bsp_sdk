
1）功能说明：
此sample是爱芯SDK包提供的示例参考代码, 演示如何对一个输入yuv切多份，并通过IVPS做CropResize，再送JENC编码。

2）使用示例：
举例一：查看help信息
/ # ./sample_ivps_jenc_slice -h
Usage:./sample_ivps_jenc_slice -h for help

        e.g: sample_ivps_jenc_slice -w 2688 -h 1520 -W 4608 -H 2592 -i nv12_2688x1520.yuv -j 1 -n 2
        w: width of src frame
        h: height of src frame
        W: width of dst frame
        H: height of dst frame
        i: input yuv file path
        j: jenc channel count,default 1
        l: enable loop encode,0:disable 1:enable,default 0
        m: want to encode how many frames,default 1
        n: slice number,default 1,whitch means one full frame
        s: whether write output stream to file,0:don't wirte 1:wirte,default 1
