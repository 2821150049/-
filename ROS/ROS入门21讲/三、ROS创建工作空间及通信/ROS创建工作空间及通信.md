# ROS创建工作空间及通信

## 创建工作空间及功能包

+ 工作空间（wokespace）：是一个存放工程开发相关文件的文件夹

  + src：代码空间、放置功能包入package
  + build：编译空间
  + devel：开发空间、可执行文件库，脚本
  + install：安装空间

+ 创建工作空间

  + 创建工作空间

    + ```C
      mkdir -p catkin_ws/src  // 创建文件夹
      cd catkin_ws/src     //到src文件夹下
      catkin_init_wokespace  //初始化工作空间
      ```

  + 编译工作空间

    + ```C
      cd ~/catkin_ws/   // 到catkin_ws工作目录下
      catkin_make		//编译环境
      ```

  + 设置环境变量

    + ```C
      gedit ~/.bashrc    // 打开.bashrc文件
      // 粘贴：source ~/catkin_ws/devel/setup.bash
      ```

+ 创建功能包`catkin_create_pkg packge_name depend1`[^1]

  + ```C
    cd ~/catkin_ws/src  //到src文件下
    catkin_create_pkg test_pkg std_msgs rospy roscpp  //创建功能包
    cd ~/catkin_ws //到catkin_ws下
    catkin_make //编译功能包
    ```

## 发布者Publisher的编程实现

+ 话题模型![1](img\1.png)

+ 创建功能包

  + 上一个功能包可以直接删除，因为当时只是练习，并且一个工作空间下可以有很多功能包

  + ```C
    cd ~/catkin_ws/src  //到src文件下
    catkin_create_pkg learning_topic roscpp rospy std_msgs geometry_msgs turtlesim //创建功能包
    ```

  + 在生成的learning_topic文件夹下的src文件夹中创建发布者代码（C++）(可以直接使用教程代码)

  + 在CMakeLists.txt文件中加入编译指令和设置链接库

    + ```cmake
      add_executable(velocity_publisher src/velocity_publisher.cpp)  # 添加编译选项
      target_link_libraries(velocity_publisher ${catkin_LIBRARIES}) # 设置动态链接库
      ```

  + ```C
    cd ~/catkin_ws // 到catkin_ws文件夹下
    catkin_make // 编译工作空间
    ```

  + 运行小海龟

    + ```C
      roscore  //运行Rosmaster
      rosrun turtlesim turtlesim_node  //运行小海龟节点
      rosrun learning_topic velocity_publisher //运行发布者
      ```

+ 代码的实现过程

  + ![3](img\3.png)

## 订阅者Subscriber编程实现

+ 话题模型![2](img\2.png)
+ 在上个功能包中粘贴pose_subscriber.cpp文件
+ 编译的操作方法和上面一样

+ 代码实现过程：
  + ![4](img\4.png)

## 话题消息的定义与使用

+ 服务模型![5](img\5.png)

+ 自定义服务数据

  + 在功能包中创建srv文件夹，并在其中创建Person.srv文件，

    ```C
    // 写入数据类型
    string name
    uint8 age
    uint8 sex
    uint8 unknown = 0
    uint8 male = 1
    uint8 female = 2
    ---
    string result
    ```

  + 在package.xml中添加功能包依赖

    ```xml
    <build_depend>message_generation</build_depend>
    <exec_depend>message_runtime</exec_depend>
    ```

  + 在CMakeLists.txt添加编译选项

    ```cmake
    find_package( …… message_generation)
    add_service_files(FILES Person.srv)
    generate_messages(DEPENDENCIES std_msgs)
    catkin_package(…… message_runtime)
    ```

  + 编译工作空间

+ 创建服务器代码

+ 创建客户端代码

+ 配置服务器/客户端代码编译规则

  ```cmake
  add_executable(person_server src/person_server.cpp)
  target_link_libraries(person_server ${catkin_LIBRARIES})
  add_dependencies(person_server ${PROJECT_NAME}_gencpp)
  add_executable(person_client src/person_client.cpp)
  target_link_libraries(person_client ${catkin_LIBRARIES})
  add_dependencies(person_client ${PROJECT_NAME}_gencpp)
  ```

+ 编译并运行客户端和服务端



[^1]: package_name是自定义包名，depend1是依赖项