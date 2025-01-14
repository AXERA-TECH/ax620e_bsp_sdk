
1）功能说明：

该模块是爱芯SDK包提供的IVE（智能视频分析引擎）单元示例代码，方便客户快速理解和掌握IVE相关接口的使用。
sample_ive，位于/opt/bin目录，可用于IVE接口示例。

参数描述如下：
-c | --case_index: 算子测试索引，默认：0
    0-DMA 直接内存访问。
    1-DualPicCalc 二图简单计算（包括Add、Sub、And、Or、Xor、Mse）。
    2-HysEdge/CannyEdge 边缘提取。
    3-CCL 连通区域标记。
    4-Erode/Dilate 腐蚀、膨胀。
    5-Filter 5x5模板滤波测试
    6-Hist/EqualizeHist 直方图统计、直方图均衡化。
    7-Integ 积分图统计。
    8-MagAng 梯度幅值和幅角计算。
    9-Sobel 5x5模板Sobel-like梯度计算。
    10-GMM2 GMM2高斯背景建模。
    11-Thresh 阈值化计算。
    12-16BitTo8Bit 16bit到8bit图像数据线性转化。
    13-多算子组链测试（DMA-Sub-Hist）。
    14-Map 映射赋值
    15-Lbp 局部二值模式计算
    16-OrdStatFltBern 顺序统计量滤波及Bernsen阈值计算
    17-Corner 灰度图像的角点计算
    18-LkOpticalFlow LK光流计算
    19-Ncc 归一化互相关计算
    20-Sad 绝对误差和计算
-e | --engine_choice: 引擎选择
    0-IVE; 1-TDP; 2-VGP; 3-VPP; 4-GDC; 5-DSP; 6-NPU; 7-CPU.
-m | --mode_choice: 测试模式选择，默认：0
    对于DualPicCalc, 指示两图像计算任务类别:
        0-add; 1-sub; 2-and; 3-or; 4-xor; 5-mse.
    对于HysEdge/CannyEdge，指示HysEdge或CannyEdge计算:
        0-hys edge; 1-canny edge.
    对于Erode/Dilate，指示Erode或Dilate计算:
        0-erode; 1-dilate.
    对于Hist/EqualizeHist测试，指示Hist或EqualizeHist计算:
        0-hist; 1-equalize hist.
-t | --type_image: 图像类型索引（如果是IVE引擎具体参见AX_IVE_IMAGE_TYPE_E枚举，其他引擎具体参见AX_IMG_FORMAT_E枚举）
    注意：
    1. 对于所有测试，输入和输出图像类型都需要按照指定的输入和输出文件的顺序来指定。
    2. 如果不指定类型，即传入的类型值为-1，则按照API文档限定指定一个合法的类型。
    3. 多个输入输出图像类型，由空格分开。
    4. 一维数据类型（比如AX_IVE_MEM_INFO_T类型）不要求指定类型。
-i | --input_files: 输入图像（或数据）文件，如果有多个输入，由空格分开。
-o | --output_files: 输出图像（或数据）文件或目录，如果有多个输出，由空格分开
    注意：
    1. 具体可参考/opt/data/ive/目录下各个测试用例对应目录下的json文件。
    2. 对于DMA、CCL的blob连通区域信息，输出必须指定为目录。
-w | --width: 输入图像宽，默认：1280。
-h | --height: 输入图像高，默认：720。
-p | --param_list: 控制参数列表或文件（按照json数据格式）
    注意：对于MagAng不需要指定。
-a | --align_need: 宽、高和stride是否需要自动对齐，默认：0
    0-no; 1-yes.
-? | --help: 显示用法帮助。


2）使用示例：

举例一：查看help信息
./sample_ive -?

举例二：DMA内存拷贝测试（源图像分辨率：1280x720，输入输出类型：U8C1，json配置文件指定控制参数）
./sample_ive -c 0 -w 1280 -h 720 -i /opt/data/ive/common/1280x720_u8c1_gray.yuv -o /opt/data/ive/dma/ -t 0 0 -p /opt/data/ive/dma/dma.json

举例三：MagAndAng梯度幅值和幅角计算测试（图像分辨率：1280x720，输入grad_h、grad_v和输出mag_output的类型：U16C1，输出ang_output的类型：U8C1）
./sample_ive -c 8 -w 1280 -h 720 -i /opt/data/ive/common/1280x720_u16c1_gray.yuv /opt/data/ive/common/1280x720_u16c1_gray_2.yuv -o /opt/data/ive/common/mag_output.bin /opt/data/ive/common/ang_output.bin -t 9 9 9 0

举例四：GMM2测试（GMM2，1280x720，输入图像、输出前景和背景图像类型：U8C1，json字符串指定控制参数）
./sample_ive -c 10 -w 1280 -h 720 -i /opt/data/ive/gmm/gmm2/gmm2_1280x720_u8c1_gray.yuvv /opt/data/ive/gmm/gmm2/gmm2_gray_1280x720_model.bin -o /opt/data/ive/gmm/gmm2/gmm_output_fg.bin /opt/data/ive/gmm/gmm2/gmm_output_bg.bin /opt/data/ive/gmm/gmm2/gmm_output_model.bin -t 0 0 0 -p {\"init_var\":202820,\"min_var\":110515,\"max_var\":197086,\"lr\":114,
\"bg_r\":124,\"var_thr\":84,\"var_thr_chk\":243,\"ct\":31,\"thr\":199}


3）运行结果：

运行成功后，会在指定目录下产生指定图像（或数据）。


4）注意事项：

    a)示例代码仅作为API演示；在实际开发中，用户需结合具体业务场景配置参数。
    b)参数约束具体参考《42 - AX IVE API 文档》。
    c)输入输出内存由用户提供。
    d)用户必须指定输入输出图像（或数据）。
    e)不同算子要求的输入输出图像（或数据）个数可能不一样。
    f)二维图像类型必须一一指定，如果不指定按默认值。
    h)控制参数按json字符串或json文件指定（部分算子不需要控制参数），参数关键字固定，具体可参考/opt/data/ive下各个测试目录下的.json文件或者程序。


5）json文件中关键字说明：

    （1）dma.json：mode、x0、y0、h_seg、v_seg、elem_size、set_val分别对应DMA控制参数AX_IVE_DMA_CTRL_T结构体中的
        enMode、u16CrpX0、u16CrpY0、 u8HorSegSize、u8VerSegRows、u8ElemSize、u64Val；
        w_out和h_out分别对应输出图像宽度和高度，仅AX_IVE_DMA_MODE_DIRECT_COPY模式使用。
    （2）dualpics.json：x、y分别对应Add控制参数AX_IVE_ADD_CTRL_T结构体中的u1q7X、u1q7Y。
        mode对应Sub控制参数AX_IVE_SUB_CTRL_T结构体中的enMode。
        mse_coef对应Mse控制参数AX_IVE_MSE_CTRL_T结构体中的u1q15MseCoef。
    （3）ccl.json：mode对应CCL控制参数AX_IVE_CCL_CTRL_T结构体中的enMode。
    （4）ed.json：mask对应Erode控制参数AX_IVE_ERODE_CTRL_T或Dilate控制参数AX_IVE_DILATE_CTRL_T结构体中的au8Mask[25]。
    （5）filter.json：mask对应Filter控制参数AX_IVE_FILTER_CTRL_T结构体中的as6q10Mask[25]。
    （6）hist.json：histeq_coef对应EqualizeHist控制参数AX_IVE_EQUALIZE_HIST_CTRL_T结构体中的u0q20HistEqualCoef。
    （7）integ.json：out_ctl对应Integ控制参数AX_IVE_INTEG_CTRL_T结构体中的enOutCtrl。
    （8）sobel.json：mask对应Sobel控制参数AX_IVE_SOBEL_CTRL_T结构体中的as6q10Mask[25]。
    （9）gmm2.json：init_var、min_var、max_var、lr、bg_r、var_thr、var_thr_chk、ct、thr分别对应GMM2控制参数AX_IVE_GMM2_CTRL_T结构体中
        的u14q4InitVar、u14q4MinVar、u14q4MaxVar、u1q7LearnRate、u1q7BgRatio、u4q4VarThr、u4q4VarThrCheck、s1q7CT、u8Thr。
    （10）thresh.json：mode、thr_l、thr_h、min_val、mid_val、max_val分别对应Thresh控制参数AX_IVE_THRESH_CTRL_T结构体中的
        enMode、u8LowThr、u8HighThr、u8MinVal、u8MidVal、u8MaxVal。
    （11）16bit_8bit.json：mode、gain、bias分别对应16BitTo8Bit控制参数AX_IVE_16BIT_TO_8BIT_CTRL_T结构体中的enMode、s1q14Gain、
        s16Bias。
