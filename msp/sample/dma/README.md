# 本测试用来测试dmadim各个模式的API是否正常

### 介绍
+ 测试memset功能
+ 测试checksum功能
+ 测试1D/D/3D/4D copy功能
+ 测试各功能的同步，异步模式

### 使用
+ sample路径及名字 map/out/bin/sample_dma
+ 执行方法 ./sample_dma
+ 测试通过终端会打印“test successful.”，失败会打印“test failed!”及fail函数信息，行号等