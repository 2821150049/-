# CMake和XML

## 一、认识CMake

1. *什么是CMake*:CMake是跨平台编译器
2. 创建CMake文件时名字是大小写相关的、需要确保每一个目录都存在一个CMakeLists.txt文件。

## 二、CMake常用指令

1. **==cmake_minimum_required==**：指定CMake的最小版本需求。

   > 语法

   ```cmake
   cmake_minimum_required(VERSION 版本号)
   # 例如
   cmake_minimum_required(VERSION 2.8.3)
   ```

2. **==project==**：指定CMake的项目名称。

   > 语法

   ```cmake
   project(projectname [CXX][C][Python])
   # 例如
   project(HELLOWORLD)
   ```

3. **==set==**：显示定义变量。

   > 语法

   ```cmake
   set(VAR [VALUE])
   # 例如,定义SRC变量，其值为main.cpp,,hello.cpp
   set(SRC main.cpp hello.cpp)
   ```

4. **==include_directories==**：向工程添加多个特定的头文件搜索路径

   > 语法

   ```cmake
   include_directories(路径)
   # 例如
   include_directories(/user/home/...)
   ```

5. **==link_directories==**：向工程添加多个特定的库文件搜索路径

   > 语法

   ```cmake
   link_directories(dir)
   # 例如
   link_directories(/user/lib/..  /lib)
   ```

6. **==add_library==**：生成库文件

   > 语法

   ```cmake
   add_library(libname [SHARED|STATIC|MODULE] source1)
   # 例如 ：SHARED（动态库）|STATIC（静态库）|MODULE] source1（源代码）
   add_library(hello SHARED ${SRC})
   ```

7. **==add_complie_options==**：添加编译参数

   > 语法

   ```cmake
   add_complie_options(<options>..)
   # 例如
   add_complie_options(-wall -std=c++11 -o2)
   ```

8. **==add_executable==**：生成可执行文件

   > 语法

   ```cmake
   add_executable(exename source1...)
   # 例如:编译main.cpp生成可执行文件main
   add_executable(main main.cpp)
   ```

## 三、认识XML

1. 什么是XML?
2. XML是一种可扩展标记语言