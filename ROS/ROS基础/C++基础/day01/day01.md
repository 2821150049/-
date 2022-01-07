# day01

[toc]

## 一、C++介绍

### 1.C++背景

```
C++ 是一种通用的，面向对象的编程语言，由Bjarne Stroustrup于1979年设计，是C语言的扩展，并提供了一些额外的功能，例如类，继承，默认函数参数等。
C ++在现代起着不可或缺的作用，因为许多现代系统（例如操作系统，Web浏览器，数据库等）在其代码库的至少某些部分中都包含C ++代码。而且，由于C ++的速度，它在性能至关重要的领域中非常有用。
```

### 2.环境准备

+ GNU:类Unix操作系统的编译标准，操作系统里内置了
+ Visual C++
+ MinGW(使用)

## 二、第一个程序和注释

### 1.第一个程序

```cpp
#include <iostream> // 导入输入输出流依赖
// main函数作为C++程序的入口、一个程序只能有一个main
int main(){
    // 打印
    std::cout << "hello C++" << std::endl;
    return 0; // 一般返回值是0、表示正常结束
}
```

### 2.注释

+ **行注释：快捷键`ctrl+/`**
+ **块注释：快捷键`ctrl+shift+/`**

### 3.快捷键

+ `ctrl+p`:查看函数参数解释
+ `ctrl+d`:快速复制当前行
+ `ctrl+shift+方向上/下`:代码换行
+ `Fn+Home/End`:光标跳到最左边或者最右边

## 三、数据类型及变量

### 1.数据类型

| 数据类型 | 声明   |
| -------- | ------ |
| 整数类型 | int    |
| 单精度   | float  |
| 双精度   | double |
| 字符     | char   |
| 字符串   | string |
| 布尔     | bool   |

```c++
#include <iostream>
/*
 * 数据类型
 */
int main(){
//    内存占8字节
    int age = 18;   // 整数
//    内存占1字节
    int8_t age2 = 14;
    char c = 'a';   // 字符
    float a = 10.5;
    double b = 20.8;
//    在C/C++中将非0看做true,0看做false
    bool f = true;
    bool f2 = false;
    return 0;
}
```

```cpp
#include <iostream>
/*
 * 数据类型
 */
int main(){
    /*数据类型占用空间的大小*/
    std::cout<<"int占的空间:" << sizeof(int) << std::endl;
    std::cout<<"char占的空间:" << sizeof(char) << std::endl;
    std::cout<<"float占的空间 " << sizeof(float) << std::endl;
    std::cout<<"double占的空间:" << sizeof(double) << std::endl;
    std::cout<<"bool占的空间:" << sizeof(bool) << std::endl;
    std::cout<<"int8_t占的空间:" << sizeof(int8_t) << std::endl;
    std::cout<<"int16_t占的空间:" << sizeof(int16_t) << std::endl;
    return 0;
}
// 结果:
/*
int占的空间:4
char占的空间:1
float占的空间 4
double占的空间:8
bool占的空间:1
int8_t占的空间:1
int16_t占的空间:2
*/
```

### 2.变量

##### 1.声明和初始化

```cpp
#include <iostream>
int main(){
    // 声明后立即初始化并赋值
    int age = 18;
    // 第二种写法, 先声明
    int score;
    // 后赋值
    score = 100;
    // C++中的赋值手法
    int a = 3;  // C语言写法
    int b(5);   // 构造的方式
    int c{4};   // C++11的时候推出的,
    std::cout<<"a="<<a<<std::endl;
    std::cout<<"b="<<b<<std::endl;
    std::cout<<"c="<<c<<std::endl;
    std::cout<<"a:占用的空间"<< sizeof(a)<<std::endl;
    return 0;
}
// 结果：
/*
a=3
b=5
c=4
a:占用的空间4
*/
```

##### 2.变量的命名规则

> 数字、字母、下划线，数字不能开头，不能有特殊字符，下划线可以开头

### 3.常量和输入输出

##### 1.常量

```cpp
#include <iostream>
/*
 * 常量：
 *     1. 与变量成相对的关系
 *     2. 变量的值可以改变,常量的值禁止改变
 */
int main(){

    int age = 18;
    age = 19;
    // 常量
    const int Months_of_year = 12;
    // 报错
    // Months_of_year = 20;
    std::cout<<"age="<<age<<std::endl;

    return 0;
}
// 运行结果：age=19
```

##### 2.输入输出

> 输入输出需要导入库`iostream`，输入是`std::cin`，输出是`std::cout`

###### 1.输出

```cpp
#include <iostream>
int main() {

    std::cout<<"你好";
    // 单纯换行
    std::cout<<std::endl;
    std::cout<<"你好"<<std::endl;
    std::cout<<"你好";
    // 不换行,换行的话加\n,或者加
    // std::endl表示输出行结束,刷新缓冲区内容
    return 0;
}
//运行结果：
你好
你好
你好
```

###### 2.输入：获取键盘内容

```cpp
#include <iostream>
int main(){

    std::cout<<"请输入你的年龄:"<<std::endl;
    int age;
    // 输入>>指向age
    std::cin>>age;
    std::cout<<"您的年龄是:"<<age<<std::endl;
    return 0;
}
// 结果：
请输入你的年龄:
12
您的年龄是:12
```

## 四、条件与循环

### 1.条件判断

#### 	1.1.if语句

```cpp
#include <iostream>
int main(){
    int age = 0;
    std::cout<<"请输入你的年龄:"<<std::endl;
    std::cin>>age;
    if(age >= 18){
        std::cout<<"可以参加选举"<<std::endl;
    }else{
        std::cout<<"在等等"<<std::endl;
    }
    return 0;
}
// 运行结果：
请输入你的年龄:
10
在等等
```

```cpp
#include <iostream>
int main(){
    std::cout<<"请输入你的成绩"<<std::endl;
    int score;
    std::cin>>score;
    if (score>=90){
        std::cout<<"允许完一会游戏"<<std::endl;
    }else if(score>=80){
        std::cout<<"允许看一会电视"<<std::endl;
    }else{
        std::cout<<"通宵写作业"<<std::endl;
    }
    return 0;
}
// 运行结果：
请输入你的成绩
90
允许完一会游戏
```

#### 1.2.switch

**注意：switch只能允许判定`char`、`int`、`枚举`**

+ 只能用于完全的等价判断
+ 可以简化我们的多个`else_if`

```cpp
#include <iostream>
int main(){

    std::cout<<"请输入这次的考试成绩:(A,B,C,D)"<<std::endl;
    char level;
    std::cin>>level;
    switch (level) {
        case 'A':
            std::cout<<level<<std::endl;
            break;
        case 'B':
            std::cout<<level<<std::endl;
            break;
        case 'C':
            std::cout<<level<<std::endl;
            break;
        case 'D':
            std::cout<<level<<std::endl;
            break;
        default:
            std::cout<<"输入错误"<<std::endl;
    }
    return 0;
}
// 运行结果：
请输入这次的考试成绩:(A,B,C,D)
A
A
```

### 2.运算符操作

+ 关系运算符
+ 逻辑运算符`&&、||、!`

```cpp
#include <iostream>
/*关系运算符*/
int main(){
    std::cout << "请输入语文成绩:" << std::endl;
    int chinese_score = 0;
    std::cin>>chinese_score;
    std::cout << "请输入数学成绩:" << std::endl;
    int math_score = 0;
    std::cin>>math_score;
    if (chinese_score >= 95 && math_score >= 95){
        std::cout<<"可以去清华附中"<<std::endl;
    } else {
        std::cout<<"可以去村里的高中"<<std::endl;
    }
    return 0;
}
// 运行结果：
请输入语文成绩:
75
请输入数学成绩:
65
可以去村里的高中
```

### 3.三元运算符

`表达式?值1:值2`

## 五、循环

### 1.while

### 2.do…while

### 3.for

### 4.break和continue

## 六、命名空间

### 1.自定义命名空间

> 存在相同的变量或者函数时，从而引入了命名空间

*定义：*`namespace 空间名{}`

*调用：*`空间名::对象`、`::`是**域**操作符

```cpp
#include <iostream>
namespace Zhangsan{
    int age = 19;
}
namespace Lisi{
    int age = 18;
}
int age = 40;   // 全局变量
int main(){
    int age = 30;   // 局部变量，程序采用就近原则
    std::cout << "age局部 = " << age << std::endl;
    // ::age访问全局变量
    std::cout << "age全局 = " << ::age << std::endl;

    std::cout << "张三的年龄" << Lisi::age << std::endl;
    std::cout << "李四的年龄" << Zhangsan::age << std::endl;
}
// 结果：
age局部 = 30
age全局 = 40
张三的年龄18
李四的年龄19
```

### 2.简化命名空间的用法

`using简化命名空间`

```cpp
#include <iostream>
// 调用命名空间
using namespace std;
namespace ZS{
    int age = 18;
}
namespace LS{
    int age = 28;
}
using namespace ZS;
int main(){
    cout<<"你好"<<endl;
    cout << "张三的年龄" << age << endl;
    cout << "李四的年龄" << LS::age << endl;
    return 0;
}
// 结果：
你好
张三的年龄18
李四的年龄28
```

## 七、数组

### 1.数组的声明和初始化（操作和C语言一样）