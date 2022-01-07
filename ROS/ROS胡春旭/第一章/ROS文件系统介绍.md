[TOC]

# ROS文件系统介绍

## 一、准备工作

1. 将会用到`ros-tutorials`程序包：

   ```C
   sudo apt-get install ros-<distro>-ros-tutorials
   //将 '<distro>' （包括'<>'）替换成你所安装的版本（比如 kinetic、melodic 等）
   ```

   输入roscore，可以看到自己的版本。

2. 文件系统概述：

   > `Packages`:软件包，是ROS应用程序代码的组织单元，每个软件包都可以包含程序可以，可执行文件，脚本或者其他手动创建的动词。
   >
   > `packages.xml`:清单，对软件包信息的描述，定义相关依赖

## 二、文件系统工具

1. `rospack`

   + ```C
     rospack find [包名称]  //返回软件包的路径信息
     ```

2. `roscd`

   + ```C
     roscd [本地包名称[/子目录]]   //直接切换工作目录到某个软件包或者软件包集当中
     ```

     **注意：就像ROS中的其它工具一样，roscd只能切换到那些路径已经包含在环境变量（ROS_PACKAGE_PATH）中的软件包，要查看环境变量中包含的路径可以输入：**`echo  $ROS_PACKAGE_PATH​`

   + 

3. `rosls`
4. `Tab自动补全`