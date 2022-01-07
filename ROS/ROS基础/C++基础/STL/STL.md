# STL

## 一、STL基本概念

### 1.STL为标准的模板库

+ 容器`container`
+ 算法`algorithim`
+ 迭代器`iterator`

### 2.STL六大组件

1. 容器：`vector/list/deque/set/map`
2. 算法：`sort/find/copy/for_each`
3. 迭代器：重载运算符
   1. `v.bigan`:起始迭代器、`v.end`:结束迭代器
4. 仿函数
5. 适配器
6. 空间配置器

### 3.常用容器

#### 3.1、`string`容器

##### 1.*赋值*

```cpp
/* string */
#include <iostream>
#include <string>
using namespace std;
int main() {
    // 构造
    string str1;
    string str2 = str1;
    string str3 = "abc";
    string str4("abc");
    string str5(5,'a');
    cout << str1 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    // 赋值
    string str6;
    // 带参数的时候，指取前3个给str5
    str6.assign("abcd",3);
    // 从的二个开始，取3个
    str6.assign("123456",2,3);
    cout << str5 << endl;
}
// 运行结果：

abc
abc
aaaaa
345
```

##### 2.*存取字符的操作*

```cpp
// 遍历字符串
// size()获取字符串长度
void text02() {
    string s = "hello world";
    for (int i = 0; i < s.size(); ++i) {
//        cout << s[i] << "-";
        cout << s.at(i) << "-";
        // []和at()区别、[]访问越界，直接挂掉，at()访问越界，会抛出异常
    }
}
// 运行结果：
h-e-l-l-o- -w-o-r-l-d-
```

##### 3.*追加*

```cpp
// +=/append()
// 拼接
void text03() {
    string str1("sss");
    str1 += "abc";
    cout << str1 << endl;
    str1.append("---");
    cout << str1 << endl;
}
// 运行结果：
sssabc
sssabc---
```

##### 4.*查找*

```cpp
// 查找
// int find(const string& str,int pos=0); 查找str第一次出现的位置，从pos开始
// int find(const char* s,int pos=0,int n); 从pos开始,的前n个字符第一次位置
// int rfind(const string& str,int pos=0); 查找str1最后一次出现的位置，从pos开始
// int rfind(const char* s,int pos=0,int n); 从pos开始,的前n个字符最后一次位置
void text04() {
    string str1("12345634789");
    int flag = str1.find("34");
    cout << flag <<endl;
    int flag2 = str1.rfind("34");
    cout << flag2 <<endl;
}
// 结果
2
2
// 找到返回角标，找不到，返回-1
```

##### 5.*替换*

```cpp
// 替换
// string& replace(int pos,int n,const string& str); 替换从pos开始n个字符为字符串str
void text05(){
    string str1 = "able cute";
    // 指定的字符串是啥，就会将指定长度部分的字符串替换进去。
    str1.replace(1,3,"-----");
    cout << str1 <<endl;
}
// 运行结果：
a----- cute
```

##### 6.*比较*:按照assii码比较，判断相等

```cpp
/*
比较
 compare函数在>时返回1,<时返回-1,==时返回0
 int compare(const string &s)
 */
void text06() {
    string str1 = "able";
    int flag = str1.compare("alll");
    cout << flag << endl;
}
// 运行结果:
-1
```

##### 7.*子串*

```cpp
/*
子串
string substr(int pos,int n); 截取字符串，并返回回来
 */
void text07(){
    string str1 = "asdfgh";
    string s = str1.substr(1,3);
    cout << s << endl;
}
```

##### 8.*插入、删除*

```cpp
/*
 * 插入和删除
 * string& insert(int pos,const string& s); 在指定位置pos插入字符串s
 * string& insert(int pos,int n,const char c); 在指定位置pos插入n个字符c
 * string& erase(int pos,int n); 删除从pos开始的n个字符
 * */
void text08() {
    string str1 = "hello world";
    string s = str1.insert(str1.find(' ')," --");
    cout << s << endl;
    string str2 = "hello world";
    string ss = str2.insert(str2.find(' '),3,'-');
    cout << ss << endl;
    string ssdel = str2.erase(str2.find(' '),1);
    cout << ssdel << endl;
}
// 运行结果:
hello -- world
hello--- world
hello---world
```

##### 9.*string和c_style字符串转换和大小写转换*

```cpp
/*
 * string和c_style字符串转换
 */
void text09() {
    string str = "hello world";
    cout << str << endl;
    const char* s_str = str.c_str();
    cout << s_str << endl;
    // 转大写
    for (int i = 0; i < str.size(); ++i) {
        str[i] = toupper(str[i]);
    }
    cout << str << endl;
    // 转小写
    for (int i = 0; i < str.size(); ++i) {
        str[i] = tolower(str[i]);
    }
    cout << str << endl;
}
// 运行结果:
hello world
hello world
HELLO WORLD
hello world
```

**使用引用时，当地址重新分配内存之后，在使用之前的引用，会报错**

#### 3.2、vector容器

1. *和数组一样，只不过vector是动态空间，但是是单端数组，和栈有点像*

![1](img\1.png)

2. *自动扩容方式：倍数扩容，动态扩展*

```cpp
void text(){
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
        // v.capacity()查看空间大小
        cout << v.capacity() << endl;
        i < 9 && cout << '-';
    }
}
// 运行结果:
1-2-4-4-8-8-8-8-16-16
```

##### 1.*vector构造函数*

```cpp
/*
vector 构造函数
    vector<T> v;默认构造函数
    T(v.begin(),v.end());从begin开始到end的前一个结束拷贝
    T(n,elem); 将n个ele拷贝个本身
    T(const vector& vec);拷贝构造函数
 */
void text02(){
    vector<int> v2(5,20);
    printVector(v2);
    vector<int> v3(v2.begin(),v2.end());
    printVector(v3);
    vector<int> v4(v3);
    printVector(v4);
}
// 运行结果：
20-20-20-20-20
20-20-20-20-20
20-20-20-20-20
```

##### 2.*遍历*

```cpp
void printVector(vector<int>&v) {
    for (vector<int>::iterator it = v.begin();it != v.end();it++) {
        cout << *it;
        it+1 != v.end() && cout << '-';
    }
    cout << endl;
}
```

##### 3.*赋值*

```cpp
/*
vector 构造函数
    vector<T> v;默认构造函数
    T(v.begin(),v.end());从begin开始到end的前一个结束拷贝
    T(n,elem); 将n个ele拷贝个本身
    T(const vector& vec);拷贝构造函数
 */
void text02(){
    vector<int> v2(5,20);
    printVector(v2);
    vector<int> v3(v2.begin(),v2.end());
    printVector(v3);
    vector<int> v4(v3);
    printVector(v4);
}
// 运行结果:
1-2-3-4-5-6
5-5-5
1-2-3-4-5-6
1-2-3-4-5-6
5-5-5
```

##### 4.*大小操作*

```cpp
/*
vector大小的操作
    V.size();返回容器中元素大小
    V.empty();判断是否为空,非空返回0,空返回1
    V.resize(int num); 重新指定人哪个区的长度,默认用0填充
    V.resize(int num,elem); 重新指定区域长度，变长,elem填充，变短，超出部分被删除
    V.capacity();容器的容量
    reserve(int len);预留长度len的空间，预留位置不初始化，元素不初始化
 */
void text04(){
    vector<int> v1{1,2,3,4,5};
    cout << "判空:" << v1.empty() << endl;
    cout << "大小:" << v1.size() << endl;
    cout << "容量:" << v1.capacity() << endl;
    printVector(v1);
    v1.resize(10);
    cout << "大小:" << v1.size() << endl;
    cout << "容量:" << v1.capacity() << endl;
    printVector(v1);
}
// 运行结果:
判空:0
大小:5
容量:5
1-2-3-4-5
大小:10
容量:10
1-2-3-4-5-0-0-0-0-0
```

##### 5.元素访问

```cpp
/*
元素访问：
    V.at();
    V[];
    V.front(); 返回第一个元素
    V.back(); 返回最后一个元素
 */
void text05(){
    vector<int> v1{1,2,3,4,5};
    vector<int>::iterator it=v1.begin();
    cout << "v1[1]=v1.at(1)=" << *(it+1) << endl;
    cout << "v1[4]=" << v1.back() << endl;
    cout << "v1[0]=" << v1.front() << endl;
}
// 运行结果:
v1[1]=v1.at(1)=2
v1[4]=5
v1[0]=1
```

##### 6.插入删除

```cpp
/*
插入和删除
    V.insert(const_iterator pos,int count,ele); pos指向的位置插入count个ele
    V.push_back(ele);尾部插入元素ele;
    V.pop_back();删除最后一个元素
    erase(const_iterator start,const_iterator end); 删除从start开始到end的元素
    erase(const_iterator pos); 删除pos指向的元素
    clear();删除所有元素
 */
void text06() {
    vector<int> v1{1,2,3,4,5};
    v1.insert(v1.begin(),1,1000);
    printVector(v1);
    v1.push_back(1000);
    printVector(v1);
    v1.pop_back();
    printVector(v1);
    v1.erase(v1.begin());
    printVector(v1);
    v1.clear();
    printVector(v1);
}
// 运行结果：
1000-1-2-3-4-5
1000-1-2-3-4-5-1000
1000-1-2-3-4-5
1-2-3-4-5
/*空行，元素全部被删除 */
```

#### 3.3、deque容器

+ *双端容器，使用需要加头文件deque*

![2](img\2.png)

##### 1.遍历、赋值、大小操作和vector一样

```cpp
/*
deque 构造函数
    deque<T> v;默认构造函数
    T(v.begin(),v.end());从begin开始到end的前一个结束拷贝
    T(n,elem); 将n个ele拷贝个本身
    T(const deque& deq);拷贝构造函数
 */

/*
deque大小的操作
    D.size();返回容器中元素大小
    D.empty();判断是否为空,非空返回0,空返回1
    D.resize(int num); 重新指定人哪个区的长度,默认用0填充
    D.resize(int num,elem); 重新指定区域长度，变长,elem填充，变短，超出部分被删除
    D.capacity();容器的容量
    D.reserve(int len);预留长度len的空间，预留位置不初始化，元素不初始化
 */
```

##### 2.插入和删除

```cpp
/*
D.push_back(num); 尾插
D.push_front(num); 头插

D.pop_back(); 尾删
D.pop_front(); 头删

元素访问：
    D.at();
    D[];
    D.front(); 返回第一个元素
    D.back(); 返回最后一个元素

插入和删除
    D.insert(const_iterator pos,int count,ele); pos指向的位置插入count个ele
    D.push_back(ele);尾部插入元素ele;
    D.pop_back();删除最后一个元素
    D.erase(const_iterator start,const_iterator end); 删除从start开始到end的元素
    D.erase(const_iterator pos); 删除pos指向的元素
    D.clear();删除所有元素
*/
```

