# day09

## 一、宏

### 1.宏变量

```c
#define PI 3.14
```

### 2.宏函数

```cpp
#define max(a,b)   ((x)+(y))
```

### 3.条件宏

```cpp
// AAAA 一般是名字
#ifdef AAAA
#define AAAA

// 函数内容

#else
#endif
```

## 二、异常

### 1.异常

### 2.不使用异常

```cpp
exit(404);// 程序结束，返回404
```

### 3.抛出异常

```cpp
throw logic_error("除数不能为零！！！");
```

### 4.捕获异常

```cpp
try{
    // 存在异常的代码
}catch(logic_error e){
    // e表示抓到的异常
    // 抓到异常了的处理代码
}catch(run_error e){
    // e表示抓到的异常
    // 抓到异常了的处理代码
}
// 可以是多个异常
```

### 5.noexcept:不会出现异常

## 三、io

### 1.打印bool值

```cpp
bool flag = false;
// 开启后，打印影响到最后
cout << boolalpha << flag << endl;
// 关闭的方式
cout << noboolalpha << flag << endl;
```

### 2.打印整数

```cpp
cout << "十进制" << dec << 8 << endl;
cout << "八进制" << oct << 8 << endl;
cout << "十六进制" << hex << 8 << endl;
```

### 3.输出浮点数

```cpp
// 加cout.precision(位数);可以打印十位
cout.precision(10);
// 默认打印6位
double pi = 3.14159265389
cout << "输出浮点数" << pi << endl;
```

### 4.输入时不忽略空格

```cpp
cin >> noskipws;
```

