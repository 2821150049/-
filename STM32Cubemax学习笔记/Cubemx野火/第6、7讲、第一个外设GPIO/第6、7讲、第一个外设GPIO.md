# 第6、7讲、第一个外设GPIO

## 一、什么是GPIO

> GPIO是通用输入输出端口的简称，简单来说就是STM32可控制的引脚，STM32芯片的GPIO引脚与外部设备连接起来， 从而实现与外部通讯、控制以及数据采集的功能。简单来说我们可以控制GPIO引脚的电平变化，达到我们的各种目的。

实物：

<img src="img\1.png" alt="1" style="zoom:50%;" />



内部结构：

![2](img\2.png)

详细图解：

<img src="img\3.png" alt="3" style="zoom:67%;" />

简化电路：

<img src="img\4.png" alt="4" style="zoom:50%;" />

## 二、编程实现

<img src="img\5.png" alt="5" style="zoom:67%;" />

1. 新建工程

![6](img\6.png)

<img src="img\7.png" alt="7" style="zoom:50%;" />

2. 注意事项：

![8](img\8.png)

3. 新建文件

<img src="img\10.png" alt="10" style="zoom:50%;" />

4. 运行环境的配置

*1.运行环境的管理工具中配置*

<img src="img\11.png" alt="11" style="zoom:50%;" />

*2.从库中添加*

<img src="img\13.png" alt="13" style="zoom:50%;" />

*3.运行，添加各种文件路径*

*4.*控制外设使能与否，就是控制这个的时钟

*5.*查看外设映射在哪个总线上

<img src="img\14.png" alt="14" style="zoom:80%;" />

5. 使能引脚时钟

<img src="img\15.png" style="zoom:67%;" />

<img src="img\16.png" alt="16" style="zoom:67%;" />

AHB外设基地址：0x4002 1000

APB2外设时钟偏移地址：0x18

APB2外设时钟使能地址：0x4002 1000+0x18

6. 配置GPIO工作模式

![17](img\17.png)

![18](img\18.png)

![19](img\19.png)

查找GPIOB外设基地址：0x40010C00

CRL偏移地址：0x00

ODR端口输出寄存器：0x0C

```C
#define GPIOB_CLK (*(volatile unsigned int *)(0x40021000 + 0x18))
#define GPIOB_CRL (*(volatile unsigned int *)(0x40010C00 + 0x00))
#define GPIOB_ODR (*(volatile unsigned int *)(0x40010C00 + 0x0C))
int main(void) {
	
	// 1.使能引脚时钟
	GPIOB_CLK |= (1<<3);
	GPIOB_CRL &= ~(0xf<<(4*1));
	GPIOB_CRL |= (2<<(4*1));
	GPIOB_ODR &= ~(0x1<<(1*1));
//	GPIOB_ODR |= (1<<0);
}
```

## 三、对比F1、F4、F7

对比发现F1和F4在GPIO结构上有巨大差异，和F7差异不大，但是编程思想差不多



## 四、库编程

用库的思想封装寄存器地址，和基本操作。