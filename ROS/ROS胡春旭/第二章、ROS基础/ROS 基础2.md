# ROS 基础

[TOC]

## 一、创建工作空间及代码包

1. *什么是工作空间？*

> 工作空间是存放工程开发相关文件的**文件夹**
>
> + `src`：代码空间，存放相关控制代码和节点代码，的文件夹
> + `buile`：编译空间，存放编译过程中产生的中间文件
> + `devel`：开发空间，存放编译完成后的可执行文件，常用

2. *创建工作空间*

> 创建并初始化工作空间

```C
mkdir -p catkin_ws/src //创建工作空间
cd ~/catkin_ws/src   //跳转到src目录下，进行工作空间的初始化
catkin_init_workspace // 初始化工作空间(需要在src文件夹下)
// Creating symlink "/home/xtark/catkin_ws/src/CMakeLists.txt" pointing to "/opt/ros/kinetic/share/catkin/cmake/toplevel.cmake"表示创建完成
```

> 编译工作空间

```C
cd .. // 必须回到catkin_ws文件夹下
catkin_make // 对工作空间进行编译
// 没有红色出现表示编译完成，且会生成devel和buile文件夹
```

>  设置环境变量

```C
source devel/setup.bash // 继续在catkin_ws下对环境变量进行配置，且设置的时候，必须在当前终端才会生效，换一个中断就没有效果
gedit ~/.bashrc  // 打开终端配置文件，配置环境变量
    source ~/工作空间的名字/devel/setup.bash
// 例如：source ~/catkin_ws/devel/setup.bash
// 配置完成后所有的终端都生效
```

> 检测环境变量

```C
echo $ROS_PACKAGE_PATH
// /home/xtark/catkin_ws/src:/opt/ros/kinetic/share 表示配置完成
```

3. *在src创建功能包*

> 创建功能包

```C
// 创建功能包需要在src代码空间中创建
cd ~/catkin_ws/src // 跳转到src目录下来
// 创建功能包
catkin_creat_pkg 功能包名字 依赖项
// 例如：catkin_creat_pkg my_ros std_msgs roscpp rospy
// Successfully created files in /home/xtark/catkin_ws/src/my_ros. Please adjust the values in package.xml. 创建成功
```

> 编译功能包

```C
cd ~/catkin_ws // 还是要在src代码空间中进行编译
catkin_make
// 没有红色出现表示编译完成
```

**当存在相同功能包时，根据ROS的Overlaying机制，即工作空间的覆盖**

## 二、ROS通信编程

1. *话题编程Topic*

> 流程：创建发布者--->创建订阅者--->添加编译选项--->运行可执行程序

> 发布者的实现：用C++编写（代码在文件中takler），初始化ROS节点--->向ROS Master注册节点（包括发布的话题名和话题中的消息类型）--->按照一定频率训话发布信息

> 订阅者的实现：用C++编写（代码在文件中listener），初始化ROS节点--->订阅需要的话题--->循环等待话题消息，接收到消息后进入回调函数--->在回调函数中完成消息处理。

> 编译代码：只有C/C++才要编译，python等不用，流程：设置需要编译的代码和生成的可执行文件；--->设置链接库--->设置依赖

+ 在工作空间的功能包(my_ros)下的src中的CMakeLists.txt里配置需要编译的代码

```C
// 用户子定义
add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
```

```C
cd ~/catkin_ws // 跳转到工作空间的目录下面
catkin_make // 编译工作空间
// 没有出现红色警告标示编译成功，会在devel的文件夹下面生成两个可执行文件
```

> 运行可执行文件：(打开的是3个新的终端)

```C
// 打开新的终端
roscore //启动rosmaster
// 打开新的终端
rosrun my_ros talker
// 打开新的终端
rosrun my_ros listener
```

+ 自定义话题消息：

> 创建自定义话题包：在功能包（my_ros）中创建
>
> 在msg中创建Person.msg文件

> 添加功能包依赖（package.xml）

```C
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```

> 添加编译选项（CMakeLists.txt）

```C
find_package(...message_generation)

add_message_files(FILES Person.msg)
generate_messages(DEPENDENCIES std_msgs)

catkin_package(...CATKIN_DEPENDS roscpp rospy std_msgs message_runtime)
```

通过命令`rosmsg show Person`可以查看是否生成成功

2. *服务编程measage*

> 流程：创建服务器--->创建客户端--->添加编译选项--->运行可执行程序

> 定义服务请求和应答：
>
> 1. 在my_ros中定义srv文件夹，在srv中导入AddTwolnts.srv文件

```C
在my_ros文件夹下的package.xml中添加
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>

// 在CMakeLists.txt中添加
//find_package(...message_generation)已经添加过就不用在添加
//catkin_package(...CATKIN_DEPENDS roscpp rospy std_msgs message_runtime)已经添加过就不用在添加
add_service_files(FILES AddTwoInts.srv)
```

> 创建服务器：（C语言实现）（代码在文档中）
>
> 流程：初始化ROS结点--->创建Server实例--->循环等待服务请求，进入回调函数--->在回调函数中完成服务功能，并反馈应答数据。

> 创建客户端：（C++语言实现）
>
> 流程：初始化ROS结点--->创建一个Client实例--->发布服务请求数据--->等待Server处理之后的应答结果。

> 编译：运行变化后产生的可执行温家岸，成功那么配置完成

3. *动作编程action*（进阶部分）

> 什么是动作（action）
>
> + 一种问答通信机制
> + 带有连续反馈
> + 可以在任务过程中终止运行
> + 基于ROS的信息机制实现
>
> Action的接口
>
> + goal：发布任务目标；
> + cancel：请求取消任务
> + status：通知客户端当前的状态
> + feedback：周期反馈任务运行的监控数据
> + result：想客户端发送任务的执行结果，值发布一次

> 1.在my_ros功能包下创建action文件夹，存放动作消息代码（代码在文件夹中）

```C
在package.xml中添加功能包依赖
  <build_depend>actionlib</build_depend>
  <build_depend>actionlib_msgs</build_depend>
  <exec_depend>actionlib</exec_depend>
  <exec_depend>actionlib_msgs</exec_depend>
在CMakeLists.txt中添加编译选项
find_package(...
  catkin REQUIRED COMPONENTS
  actionlib_msgs 
  actionlib...
)
generate_messages(... actionlib_msgs)
add_action_files(DIRECTORY action FILES DoDishes.action)
```

> 实现一个动作服务器：（C++代码实现）
>
> 初始化ROS结点--->创建动作服务器实例--->启动服务器，等待动作请求--->在回调函数中完成动作请求，并反馈进度信息--->动作完成发送结束信息。
>
> 实现一个客户端：（C++代码实现）
>
> 初始化ROS结点--->创建动作客户端实例--->连接动作服务端--->发送动作目标--->更加不同的类型的服务端反馈不同的数据类型。

## 三、分布式通信

**ROS是一种分布式的软件框架，节点之间通过松耦合的方式进行组合**

> 如何实现分布式多机通信

1. 设置IP地址，确保地城链路的联通

   ```C
   ifconfig  // 查看电脑IP地址
   ```

## 四、ROS中的关键组件

> Launch文件

**通过XML文件实现多节点配置和启动（可自动启动ROSMaster）**

```C
<launch> launch文件中的根元素采用<laubch>标签定义

// <node> 启动节点
<node pkg="package-name"type="executable-name"name="node-name"/>
pkg:节点所在的功能包名称
type:节点的可执行文件名称
name:结点运动时的名称
```

+ 参数设置

```C
// <param>/<rosparam>
<param name="out_frame"value="odom"/>
name:参数名
value:参数值
加载参数文件中的多个参数：
<rosparam file="params.yaml"command="load"ns="params"/>

// <arg>launch文件内部的局部变量，仅限于launch文件使用
<arg name="arg-name"default="arg-value"/>
name:参数名
value:参数值
```

+ 重映射

```C
//<remap>重映射ROS计算图资源的命名
<remap from="/turlebot/cmd_vel"to="/cmd_vel"/>
from:原命名
to:映射之后的命名
```

+ 嵌套

```C
//<include>包含其他launch文件，类似C语言中的头文件包含
<include file="$(dirname)/other.launch"/>
file:包含的其他launch文件路径
```



> TF坐标变换

+ 变换如何实现：广播TF变换、监听TF变换

> Qt工具箱



> Rviz可视化平台



> Gazebo物理仿真环境

