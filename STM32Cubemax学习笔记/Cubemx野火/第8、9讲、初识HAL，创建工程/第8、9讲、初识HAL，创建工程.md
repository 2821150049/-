# 第8、9讲、初识HAL，创建工程

## 一、HAL库

### 1.CMSIS 标准及库层次关系

<img src="img\1.png" alt="1" style="zoom:80%;" />

### 2.HAL库固件包内容

![2](img\2.png)

1. Documentation 文件夹：说明文档，如何使用HAL库固件包。
2. Drivers 文件夹：包含BSP\CMSIS\HAL_Driver这三个文件夹。其中，BSP为官方开发板的支持库包。CMSIS为前面讲述的CMSIS 标准除外设驱动外的各种接口库。HAL_Driver就是HAL库驱动包了。
3. Middlewares 文件夹：中间件，提供一些对硬件的服务。其中ST文件夹下为ST官方的中间件，包含emWIN图形界面库和USB主\从机接口库。Third_Party为第三方的中间件，如FatFs文件系统、FreeRTOS实时系统、LwIP网络协议栈。
4. Projects 文件夹：官方开发板的各种工程实例，包含各种外设如何使用，以及外设与中间件的耦合。非常有参考价值。
5. Utilities 文件夹：通用的一些文件，比如官方实例中用到的一些音频、视频、字库资料。不重要。

### 3.CubeMX创建工程

1. 板级支持包路径修改

![3](img\3.png)

2. 界面

<img src="img\4.png" alt="4" style="zoom:67%;" />



3. 板卡选择

<img src="img\5.png" alt="5" style="zoom:80%;" />

4. GPIO介绍

![6](img\6.png)

5. SW下载

<img src="img\7.png" alt="7" style="zoom:67%;" />



6. 组件添加

![6](img\8.png)

7. 时钟不一定要配置

8. 生成代码界面设置

![9](img\9.png)

![10](C:\Users\zhf28\Desktop\学习笔记\STM32Cubemax学习笔记\Cubemx野火\第8、9讲、初识HAL，创建工程\img\10.png)

![11](img\11.png)

