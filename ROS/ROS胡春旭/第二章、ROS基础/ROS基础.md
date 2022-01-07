[TOC]

# ROS基础

## 一、创建工作空间

#### 1. 什么是工作空间：

**工作空间是一个存放工程开发相关文件的文件夹,也可以看做是一个工程**

+ > src:代码空间、功能包源码
  >
  > buile:编译空间、中间文件、使用较少
  >
  > devel:开发空间、可执行文件、脚本
  >
  > install:安装空间、编译之后的可执行文件

#### 2.创建工作空间

+ 命令行操作

+ ```C
  /*------------------创建工作空间------------------*/
  mkdir ROS // 创建工作总空间，以后所有项目全放这里面
  cd ROS  // 跳转到ROS文件夹下
  mkdir catkin_ws  // 创建空间，也就是文件夹
  cd catkin_ws // 跳到catkin_ws文件夹下
  mkdir src // 创建代码空间
  /*------------------编译工作空间------------------*/
  cd src // 进入src文件夹下
  catkin_init_workspace // 初始化工作空间
  // 出现Creating symlink "/home...cmake"表示初始化成功
  // 会告诉系统，这就是工作空间，可以编译工作空间
  cd ..// 跳回上级目录catkin_ws
  catkon_make // 编译工作空间
  // 出现Running command 编译成功，且会生成devel和buile文件夹
  /*------------------设置环境变量------------------*/
  // 进入catkin_ws文件夹下
  source devel/setup.bash
  //什么都不出现表示设置成功、这个命令只会在同一个终端下生效
  /*------------------检测环境变量------------------*/
  echo $ROS_PACKAGE_PATH
  //会出现工作空间环境变量的路径
  /home/ubuntu/ROS...share
  ```

#### 3.创建功能包

+ 命令行操作

+ ```C
  /*------------------创建功能包------------------*/
  // 跳转到src文件夹下
  cd ~/ROS/catkin_ws/src
  // 创建功能包
  //catkin_creat_pkg <名字> [依赖][依赖]...
  catkin_creat_pkg learing_communication std_msgs rospy roscpp
  // std_msgs：ROS定义好的标准数据结构
  // rospy roscpp：编程依赖
  // 出现日志信息，说明完成
  // learing_communication中的CMakeLists.txt是编译功能包的编译选项、package.xml是描述功能包的具体信息
  /*------------------编译功能包------------------*/
  cd ~/ROS/catkin_ws //跳转到catkin_ws目录下面
  catkin_make 编译工作空间
  source ~/ROS/catkin_ws/devel/setup.bash //设置环境变量，这一步可以不用操作，之前已经设置过环境变量了，用于刷新环境
  ```

+ **注意：同一个工作空间下，不允许存在同名功能包，不同工作看见下，允许存在同名功能包** 

+ 当有多个工作空间时，会被覆盖

## 二、ROS通信编程

#### 1.话题编程Topic

+ 话题编程流程：

+ > 创建发布者：用代码实现
  >
  > 1. 初始化ROS结点：![1](msg\1.png)
  > 2. 向ROS Master注册结点信息，包括发布的话题名和话题中发消息类型![2](msg\2.png)
  > 3. 按照一定频率循环发布消息![3](msg\3.png)
  >
  > 创建通信代码：
  >
  > 1. 在`learing_communication\src`中创建`talker.cpp`文件
  >
  > + ```C++
  >   /**
  >    * 该例程将发布chatter话题，消息类型String
  >   */
  >   # include <sstream>
  >   # include "ros/ros.h"
  >   # include "std_msgs/String.h"
  >   
  >   int main(int argc, char **argv)
  >   {
  >   	// ROS节点初始化
  >   	ros::init(argc, argv, "talker");
  >       // 创建节点句柄
  >   	ros::NodeHandle n;
  >   	// 创建一个Publisher，发布名为chatter的topic，消息类型为std_msgs::String
  >   	ros::Publisher chatter_pub = 			n.advertise<std_msgs::String>("chatter", 1000);
  >   	// 设置循环的频率
  >   	ros::Rate loop_rate(10);
  >   	int count = 0;
  >   while (ros::ok())
  >   {
  >   	// 初始化std_msgs::String类型的消息
  >   	std_msgs::String msg;
  >   	std::stringstream ss;
  >   	ss << "hello world " << count;
  >   	msg.data = ss.str();
  >   	// 发布消息
  >   	ROS_INFO("%s", msg.data.c_str());
  >   	chatter_pub.publish(msg);
  >   	// 循环等待回调函数
  >   	ros::spinOnce();
  >   	// 按照循环频率延时
  >   	loop_rate.sleep();
  >   	++count;
  >   }
  >   return 0;
  >   }
  >   ```

+ > 补充：在18.04版本后，右击添加文档的方式被取消了，所以安装步骤可以添加这个功能
  >
  > 1. 看主目录下面是否有Templates，如果没有用`mkdir Templates`创建
  > 2. `cd Templates`进入这个文件夹
  > 3. ` touch "Empty Document"`创建这个文件，然后打开行动文件管理器就可以了

+ > 创建订阅者
  >
  > 1. 初始化ROS结点![1](msg\5.png)
  > 2. 订阅需要的话题![1](msg\6.png)
  > 3. 循环等待话题消息，解锁到小写后进入回调函数
  > 4. 在回调函数中完成消息处理![1](msg\7.png)
  >
  > 创建订阅者代码
  >
  > + 在`learing_communication\src`中创建`listener.cpp`文件
  >
  > + ```C++
  >   /**
  >    * 该例程将订阅chatter话题，消息类型String
  >   */
  >   # include "ros/ros.h"
  >   
  >   # include "std_msgs/String.h"
  >   
  >   // 接收到订阅的消息后，会进入消息回调函数
  >   void chatterCallback(const std_msgs::String::ConstPtr& msg)
  >   {
  >   	// 将接收到的消息打印出来
  >   	ROS_INFO("I heard: [%s]", msg->data.c_str());
  >   }
  >   
  >   int main(int argc, char **argv)
  >   {
  >   	// 初始化ROS节点
  >   	ros::init(argc, argv, "listener");
  >       // 创建节点句柄
  >   	ros::NodeHandle n;
  >   	// 创建一个Subscriber，订阅名为chatter的topic，注册回调函数chatterCallback
  >   	ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  >   	// 循环等待回调函数
  >   	ros::spin();
  >   	return 0;
  >   }
  >   ```

+ > 添加编译选项：C++才需要添加，若是py可以不添加
  >
  > 1. 在`\learning_communication\CMakeLists.txt`中添加编译选项
  >
  > 2. 先打开文件
  >
  >    + 添加,多个cpp文件需要编译时在talker.cpp后面加文件名
  >
  >    + ```C
  >      add_executable(talker src/talker.cpp)
  >      target_link_libraries(talker ${catkin_LIBRARIES})
  >      ```
  > 3. 跳转到`catkin_ws` 文件加下进行编译：
  >
  > ```c++
  > catkin_make
  > // 当编译结束后100%前面没有红色错误，说明编译成功
  > ```

+ > 运行可执行程序
  >
  > 1. 启动ROSmaster：`roscore` 是你在运行所有ROS程序前首先要运行的命令
  >    + 打开新的终端输入`roscore`启动ROSMaster
  > 2. 启动talker
  >    + 打开新的终端输入`rosrun learning_communication talker`
  > 3. 启动listerner
  >    + 打开新的终端输入`rosrun learning_communication listener`
  > 4. //`rosrun rqt-graph rqt_graph`查看结点图

$\color{red}若在运行的过程中出现无法找到包的情况，一般情况下是环境变量没有配置好​$

> 环境配置：
>
> 1. ```C
>   gedit ~/.bashrc // 打开环境配置终端
>   2. 粘贴环境变量：`source 环境变量路径`
>   3. source ~/ROS/catkin_ws/devel/setup.bash
>   ```

+ 自定义话题数据

+ > 过程：
  >
  > 1. 定义`msg/xxxx.msg`文件，在自己创建的功能包下面，就是`catkin_ws/src/learning_communication`
  >
  > 2. 在`package.xml`中添加功能包依赖
  >
  >    + ```C
  >      <exec_depend>message_runtime</exec_depend>
  >      <build_depend>message_generation</build_depend>
  >      ```
  >
  > 3. ```c++
  >     在CMakeLists.txt添加编译选项
  >    find_package(catkin REQUIRED COMPONENTS
  >    roscpp
  >    rospy
  >    std_msgs
  >    message_generation
  >    actionlib_msgs 
  >    actionlib
  >    )
  >    
  >    catkin_package(
  >    #  INCLUDE_DIRS include
  >    #  LIBRARIES learning_communication
  >    CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  >    #  DEPENDS system_lib
  >    )
  >    
  >    add_message_files(FILES Person.msg)
  >    generate_messages(DEPENDENCIES std_msgs actionlib_msgs)
  >    ```
  > 4. 查看是否定义成功：`rosmsg show 定义的msg文件名`

#### 2.服务编程

+ 服务编程流程

+ > 1. 创建服务器
  > 2. 创建客户端
  > 3. 添加编译选项
  > 4. 运行科执行程序

#### 3.动作编程

## 三、试下分布式通信



## 四、ROS中的关键组件