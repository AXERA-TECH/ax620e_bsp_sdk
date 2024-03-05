# NPU Samples

`NPU Samples` 提供运行 `Pulsar2` 编译生成的 `axmodel` 模型的 npu example 代码，是 `AX630C/AX620V200/AX620Q` 智能算法模型运行的必要示例。

已验证硬件平台

- AX620E

## 1. 示例分类

### 1.1 NPU 模型推理：

- 分类模型

  - MobileNetv1
  - MobileNetv2
  - Others

- 检测模型

  - YOLOv5s

## 2. 运行示例

### 2.1 运行准备

对于 AX630C DEMO 开发板，无需其他准备动作，运行所需的模型和图片文件已经存在于 `/opt/data/npu` 目录下，可执行 sample 已经存在于 `/opt/bin/` 目录下。
对于 AX620Q DEMO 开发板，首先需要准备一个可以 mount 到板子上的目录，然后从解压缩的 SDK 中复制 `msp/out/data/npu` 目录，从 `msp/out/bin` 目录复制
 `sample_npu_classification` `sample_npu_yolov5s` 到该可 mount 目录下。为了方便说明，下面的示例以 AX630C 的默认目录为例，AX620Q
对于 AX620V200 开发板，根据实际情况，参考以上两个开发板步骤即可。

准备完成后查看路径：
```
root@ax620e:~# tree /opt/data/npu/
/opt/data/npu/
|-- images
|   |-- cat.jpg
|   `-- dog.jpg
`-- models
    |-- mobilenetv2.axmodel
    `-- yolov5s.axmodel

root@ax620e:~# ls /opt/bin/sample_npu_*
/opt/bin/sample_npu_classification  /opt/bin/sample_npu_classification_s  /opt/bin/sample_npu_yolov5s  /opt/bin/sample_npu_yolov5s_s
```

### 2.2 分类模型

```bash
root@ax620e:~# /opt/bin/sample_npu_classification -m /opt/data/npu//models/mobilenetv2.axmodel -i /opt/data/npu/images/cat.jpg --repeat 100
--------------------------------------
model file : mobilenetv2.axmodel
image file : cat.jpg
img_h, img_w : 224 224
--------------------------------------
Engine creating handle is done.
Engine creating context is done.
Engine get io info is done.
Engine alloc io is done.
Engine push input is done.
--------------------------------------
topk cost time:0.10 ms
9.7150, 283
9.3965, 285
8.9187, 281
8.2816, 282
7.4853, 463
--------------------------------------
Repeat 100 times, avg time 0.82 ms, max_time 0.83 ms, min_time 0.82 ms
--------------------------------------
```

### 2.3 检测模型

```bash
root@ax620e:~# /opt/bin/sample_npu_yolov5s -m /opt/data/npu//models/yolov5s.axmodel -i /opt/data/npu/images/dog.jpg -r 100
--------------------------------------
model file : yolov5s.axmodel
image file : dog.jpg
img_h, img_w : 640 640
--------------------------------------
Engine creating handle is done.
Engine creating context is done.
Engine get io info is done.
Engine alloc io is done.
Engine push input is done.
--------------------------------------
post process cost time:2.41 ms
--------------------------------------
Repeat 100 times, avg time 8.16 ms, max_time 8.17 ms, min_time 8.15 ms
--------------------------------------
detection num: 3
16:  92%, [ 133,  211,  313,  546], dog
 2:  72%, [ 468,   73,  691,  174], car
 1:  56%, [ 163,  123,  571,  415], bicycle
--------------------------------------
```
