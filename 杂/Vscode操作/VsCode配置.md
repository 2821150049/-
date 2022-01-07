# VsCode配置

## 1.快捷键

| 功能                  | 快捷键             | 功能                     | 快捷键          |
| --------------------- | ------------------ | ------------------------ | --------------- |
| 转到文件/其他常用操作 | `Ctrl + P`         | 关闭当前文件             | `Ctrl + W`      |
| 打开命令面板          | `Ctrl + Shift + P` | 当前行上移/下移          | `Alt + Up/Down` |
| 打开终端              | `Ctrl + ‘`         | 变量统一重名             | `F2`            |
| 关闭测栏              | `Ctrl + B`         | 转到定义处               | `F12`           |
| 代码格式化            | `Shift + Alt + F`  | 在当前行下面插入一行新行 | `Ctrl + Enter`  |
| 查找                  | `Ctrl + F`         | 替换                     | `Ctrl + H`      |

## 2.CMake配置编译C

### 2.1CMake语法特性

1. 基本语法格式：指令(参数1 参数2)
   + 参数使用*括号*括起来
   + 参数之间使用 **空格** 或 **分号**分开
2. 指令是大小写无关的，参数和变量是大小写有关的

```cmake
set(HELLO hello.cpp)
add_executable(hello main.cpp hello.cpp)
ADD_EXECUTABLE(hello main.cpp ${HELLO}$)
```

**变量使用${}方式取值，但是IF控制语句中直接使用变量名**

### 2.2重要的指令和CMake常用变量

1. 重要指令

   + ==cmake_minimum_required==-指定CMake的最小版本要求

   ```cmake
   # 语法：cmake_minimum_required(VERSION versionNumber [FATAL_ERROR])
   # 参数1：VERSION（不用变）
   # 参数2：版本号
   # 参数3：选项，不符合最小版本要求的时候可以报一个警告或者错误
   cmake_minimum_required(VERSION 3.0)
   ```

   + ==project==-定义工程名称，并可指定工程支持的语言

   ```cmake
   # 语法：project(projectname [CXX] [C] [Java])
   # 参数1：工程名（为工程命名）
   # 参数2：[]选择支持的语言，也可以认为是可选项
   project(HELLOWORLD)
   ```

   + ==set==-显示的定义变量

   ```cmake
   # 语法：set(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
   # 参数1：定义的变量
   # 参数2：变量的值，可以是数，也可以是文件名
   set(SRC sayhello.cpp hello.cpp)
   ```

   + ==include_directories==-向工程添加多个特定的头文件搜索路径

   ```cmake
   # 语法：include_directories([绝对路径] [相对路径])
   include_directories(/user/lib/mylib ./lib)
   # 将/user/lib/mylib 和 ./lib添加到头搜索路径
   ```

   + ==link_directories==-向工程添加多个库文件路径

   ```cmake
   # 语法：link_directories(dir1 dir2...)
   link_directories(/user/lib/mylib ./lib)
   # 将/user/lib/mylib 和 ./lib添加到库搜索路径
   ```

   + ==add_library==-生成库文件

   ```cmake
   # 语法：addlibrary(libname [SHARED|STATIC|MODULE] [EXCLDE_FROM_ALL]source1 source2....sourceN)
   add_library(hello SHARED ${SRC})
   # SHARED 可选项生成动态库
   # STATIC 可选项生成静态库
   ```

   + ==add_compile_options==-添加编译参数

   ```cmake
   # 语法：add_compile_options(<option> ...)
   add_compile_options(-wall -std=c++11 -o2)
   ```

   + ==add_executable==-生成可执行文件

   ```cmake
   # 语法：add_executable(exename source1 source2 ...sourceN)
   add_executable(main main.cpp)
   ```

   + ==target_link_libraries==-为target添加需要的链接共享库

   ```cmake
   # 语法：target_link_libraries(target library1<debug | optimized> library2...)
   target_link_libraries(main hello)
   ```

   + ==add_subdirectory==-向当前工程添加存放源文件子目录，并可以指定中间二进制和目标进制存放位置

   ```cmake
   # 语法：add_subdirectory(source_dir)
   add_subdirectory(src)
   ```

   

2. 常用变量

   + ==CMAKE_C_FLAGS==-gcc编译选项
   + ==CMAKE_CXX_FLAGS==-g++编译选项
   + ==CMAKE_BUILD_TYPE==-编译类型（Debug,Release）

   ```cmake
   # 设置编译类型为debug
   set(CMAKE_BUILD_TYPE Debug)
   # 设置编译类型为Release
   set(CMAKE_BUILD_TYPE Release)
   ```

   + ==EXECUTABLE_OUTPUT_PATH==-指定可执行文件输出的存放路径

### 2.3CMake编译工程

存在两种编译规则

1. 两种方式设置编译规则



2. 两种构建方式

   1. 内部构建：不推荐

   内部构建会在同级目录下产生一大堆中间文件，这些中间文件并不是我们最终需要的，和工程源文件放在一起回显得杂乱无章

   ```bash
   # 内部构建
   # 在当前目录下，编译目录的CMakeList.txt,生成Makefile和其他文件
   cmake .
   # 执行make命令，生成target
   make
   ```

   2. 外部构建：推荐使用

   将编译输出文件和源文件放到不同目录中

   ```bash
   # 外部构建
   # 在当前目录下创建build文件
   mkdir build
   # 2. 进入build文件夹
   # 3. 编译上级目录的CMakeList.txt,生成Makefile和其他文件
   cmake ..
   # 4. 执行make命令,生成target
   make
   ```

   

