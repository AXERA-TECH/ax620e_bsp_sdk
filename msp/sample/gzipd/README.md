1）功能说明：
    该模块是爱芯SDK包提供的可以解压AXGZIP格式的压缩数据的示例代码， 方便客户理解和使用解压模块相关API接口函数；
    AXGZIP 压缩格式是基于爱芯自研压缩算法，和通用gzip压缩不一样。

2）使用步骤：
    2.1 在PC端，先用爱芯压缩工具生成压缩数据文件， 命令如下：
            tools/ax_gzip_tool/ax_gzip -9 ./input_file_name
            执行完成后生成后缀名是.axgzip的压缩文件， 例如: input_file_name.axgzip ,
            [提示：压缩耗时随着输入文件大小的增长而增长]

    2.2 在测试硬件板上，再用本模块的解压工具sample_gzipd 解压2.1) 步骤中生成的压缩文件 *.axgzip, 命令如下：
            ./sample_gzipd -if *.axgzip -of ./output_file_name

    2.3 判断成功的条件：
            可以使用sha1sum 命令，查看2.1)中input_file_name 和 2.2) 中 output_file_name 这2个文件的sha1sum值，如果一致，说明解压成功
