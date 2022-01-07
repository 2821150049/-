# make和cmake

## 一、make

### 1.makefile的作用

> 为了编译程序

### 2.makefile

*简单语法*

```makefile
# 目标(并不是要生成的文件，但是格式一定要有他) : 要编译的文件
#     gcc 
main:main.cpp
# 第一个文件一定要写g++ main.cpp -o main,后面的可以不用写
	gcc main.cpp -o main
```

### 3.多个文件

```makefile
main:main.cpp
	gcc main.cpp stu.cpp -o main
```

```makefile
# 单独编译，然后组合成一个
main : main.o stu.o
	g++ main.o stu.o -o main2.exe
main.o : main.cpp
	g++ -c main.cpp
stu.o : main.cpp
	g++ -c stu.cpp
```

### 4.稳健的做法

```makefile
main : main.o stu.o
	g++ main.o stu.o -o main
main.o : main.cpp
# g++ -c main.cpp
# 会自动推断，名字不能乱写，必须和.cpp名字一样
stu.o : stu.cpp
```

### 5.删除.o文件

```makefile
main : main.o stu.o
	g++ main.o stu.o -o main
main.o : main.cpp
# g++ -c main.cpp
# 会自动推断，名字不能乱写，必须和.cpp名字一样
stu.o : stu.cpp
#  删除所有.o文件
clean:
	del *.o
```

## 二、CMake

### 1.文件

`cmakelist.txt`

### 2.创建子项目

+ 一个项目有一个CMakelist文件
+ 在主文件的CMakelist.txt中添加`add_subdirectory(子项目名称)`

```cmake
# 最低支持的CMake版本
# cmake_minimum_required(VERSION 3.15)
# 添加的工程
# project(day13)
# 设置c++版本
set(CMAKE_CXX_STANDARD 14)
# 添加可执行文件
add_executable(day13 main.cpp)
```

### 3.变量和打印

+ *变量*:寄存数据、存历史路径

```cmake
# 设置变量，age(变量名) 是 18(对应的值)
set(age 18)
# 取值 ${变量名}
message(age====${age})
# 例如  路径一般加个双引号
set(opencv_dir "c:/en/opencv")
# 结果：c:/en/opencv
# 增量赋值
set(opencv_dir ${opencv_dir} "c:/en/opencv")
# 结果：c:/en/opencvc:/en/opencv
```

### 4.导入第三方库

*源码不开放，拿到的是库文件，分为静态库和动态库*

*使用的时候，不能单单的只关联头文件，还必须关联库文件*

**静态库：需要加载到程序中去**

**动态库：不需要打包到程序中去**

1. 生成动态库`shared`共享、`.so`linux的、`dll`window的

```
gcc -shared -fPIC 文件名.cpp -o 库名.dll
```

2. 使用方法

   + 导入头文件

   + 在CMakelist.txt中关联动态库

   + ```cmake
     target_link_libraries(目标 路径\文件.so)
     ```

3. 关联外部动态库

   + 关联头文件

   + ```cmake
     # 导入头文件
     include_directories("路径")
     # 关联动态库
     target_link_libraries(目标 路径\文件.so)
     ```

4. 关联多个动态库

   + 自动生成动态库的方法

   + ```cmake
     add_library(目标文件名 SHARED 文件.cpp)
     ```

   + 导头

     ```cmake
     # 可以使用多次
     include_directories("路径")
     include_directories("路径")
     ```

   + 关联库

   + ```cmake
     # 可以放多个
     target_link_libraries(目标 路径\文件.so 路径\文件.so)
     ```

5. 使用变量优化路径

   + ```cmake
     set(路径名 "路径")
     target_link_libraries(目标 ${路径名}\文件.so 路径\文件.so)
     ```

6. 查找动态库`find_library(变量 要查找的名字 路径)`

```cmake
find_library(t_lib libteacher.dll ${teacher}/lib)
```

7. 循环查找动态库

```cmake
foreach(name ${com})

endforeach()
```

8. 导包`find_package(库名)`

