# day07

## 一、继承

### 1.什么是继承

> 继承是类与类之间的关系，需要满足 `is A`:继承关系和`has A`:组合关系

### 2.继承的简单实现

```cpp
// 继承的简单实现
class Person{
    string name;
    int age;
};
class stu : public Person{
    
};
```

*继承是一种向上的抽象*

### 3.继承的访问权限

```cpp
//class stu : private Person{
/* private 修饰孩子的访问权限 */
//class stu : protected Person{
//class stu : public Person{
```

### 4.继承中的构造和析构

1. *存在继承的情况下，创建子类的对象，会执行父类的构造和子类的构造，并且，先执行父类的构造，在执行子类的构造*
2. *继承中的析构函数会先走孩子*
3. *子类的所有构造函数都只会调用父类的无参构造*
4. **需要手动调用父类中的有参构造**

```cpp
class Person{
public:
    string name;
    int age;
    Person(){
        
    }
    Person(sring name,int age):name(name),age(age){
        
    }
};
// 使用初始化列表
class stu : public Person{
public:
    stu():Person(name,age){
        
    }
};
```

### 5.再说初始化列表，必须使用的情况

1. 手动调用父类中的有参构造函数，必须要用初始化列表
2. 类中属性，是常量或者是引用类型

```cpp
class stu{
public:
    const int age;
    stu(int age):age(age){
        
    }
};
```

3. 初始化对象成员

### 6.重写父类中的成员函数

```cpp
class Person{
public:
    void smoke(){
        cout << "父亲在抽烟" << endl;
    }
};
class stu : public Person{
public:
    void smoke(){
        cout << "儿子在抽烟" << endl;
    }
};
```

### 7.多继承

*一个子类有多个父亲*

```cpp
class father{
public:
    void smoke(){
        cout << "父亲在抽烟" << endl;
    }
};
class mother{
public:
};
class son : public father,public mother{
public:
    void smoke(){
        cout << "儿子在抽烟" << endl;
    }
};
```

*多个构造的顺序是按照继承的顺序来定义的*

### 8.类的前置声明

```cpp
// 需要用引用类型，因为他不知道你的无参构造长什么样
class teacher;
class stu{
public:
    teacher& t;
};
class teacher{
    
};
```

## 二、多态

### 1.什么是多态

> 在类总存在层次结构，并且类之间是通过继承关联是，就会用到多态。

### 2.静态多态

```cpp
int add(int a,int b){
    return a + b;
}
double add(double a,double b){
    return a + b;
}
// 在编译期间就知道要用那个函数
```

### 3.动态多态

> 运行期间才知道，要用哪一个

*需要满足条件：*

1. 父类必须包含虚函数，并且子类中要对父类中的虚函数进行**重写**
2. 用父类的指针或者引用接收子类的对象，使用这个指针或者引用来调用同名的虚函数

#### 1.父类的指针接收子类对象

```cpp
class father{
public:
    void smoke(){
        cout << "父亲在抽烟" << endl;
    }
};
class son:public father{
public:
    void smoke(){
        cout << "孩子在抽烟" << endl;
    }
};
int main(){
    // 父类的指针接收父类的对象
    father * f = new father();
    f->smoke();
    // 子类的指针接收子类的对象
    son * s = new son();
    s->smoke();
    // 父类的指针接收子类的对象
    father * f1 = new son();
    f1->smoke();
}
// 结果：
父亲在抽烟
孩子在抽烟
父亲在抽烟
```

#### 2.联边机制和动态编译

```cpp
// 加virtual将同名函数变成虚函数
class father{
public:
    virtual void smoke(){
        cout << "父亲在抽烟" << endl;
    }
};
class son:public father{
public:
    // 子类重写父类函数的时候，函数类型时不会改变的，父类是虚函数，子类也是，只是隐藏起来了
    void smoke(){
        cout << "孩子在抽烟" << endl;
    }
};
int main(){
    father * f = new son();
}
// 运行结果
孩子在抽烟
```

### 3.多态的好处

+ 提高代码的健壮性

### 4.虚函数

> 1. 主要是配合父类的指针指向子类的对象，并且子类重写父类的情况下。
> 2. 构造函数禁止是虚函数
> 3. 析构函数需要加虚函数，且必须给父类加`virtual`

## 三、关键字

1. `override:`子类重写父类的函数

```cpp
class father{
public:
    // 必须是虚函数
    virtual void smoke(){
        cout << "父亲在抽烟" << endl;
    }
};
class son{
public:
    // 检测重写
    void smoke() override{
        cout << "孩子在抽烟" << endl;
    }
};
```

2. `final:`

+ 可以作用与类和函数上

```cpp
class father final{
public:
    virtual void smoke final(){
        cout << "父亲在抽烟" << endl;
    }
};
/*
会报错
class son{
public:
    // 检测重写
    void smoke(){
        cout << "孩子在抽烟" << endl;
    }
};
*/

```

3. `=delete`:表示功能禁止被使用，标记为删除，出现在拷贝构造
4. `=default`:表示默认的那一套功能，一般出现在我参构造函数上

```cpp
stu() = delete;// 删除这个拷贝构造，不能在进行
stu() = default;// 默认的那一套
```

5. 纯虚函数
   + 一般来说父类中的函数，更多是用作与声明或者是一种规定
   + 那么父类可以不用写成具体的实现
   + 如果一个类当中含有纯虚函数，那么该类即为抽象类，抽象类禁止创建对象

```cpp
class father {
public:
    // 纯虚函数
    virtual void smoke() = 0;
};
```

6. 抽象类
   + 父类中存在纯虚函数，那么就是抽象类
   + 抽象类不能创建对象
   + 如果子类继承了父类，没有实现纯虚函数，那么不能创建对象

## 四、智能指针

### 1.指针潜在问题

1. 野指针
2. 重复释放
3. 内存泄露

### 2.智能指针

*需要导入头文件`memory`*

**智能指针其实不是指针，只是一个类，用对象来包装指针**

1. `unique_ptr`:唯一指针

```cpp
unique_ptr<int> up02(new int(20));
// 特征：
```

+ 唯一智能指针，禁止发生拷贝
+ 禁止别的对象来包装这个指针
+ 获取值

```cpp
*up.get();// get()获取指针地址
*up;// 智能指针重载了*这个符号，可以直接使用这个*来解引用。
```

+ 会自动释放内存

2. `share_ptr`:共享指针

```cpp
shared_ptr<int> sp(p);
shared_ptr<int> sp1 = sp;
// 等价于
shared_ptr<int> sp = make_shared<int>(5);
// 计数
sp1.user_count();
```

+ 允许多个智能指针，包装同一个原始指针
+ 出现环形引用，无法销毁，用weak_ptr弱指针

3. `weak_ptr`:弱指针，可以接收共享指针，不会增加共享指针的计数次数

```cpp
shared_ptr<int> sp(p);
weak_ptr<int> wp(sp);
// 使用
*wp.lock();
```

### 3.应用场景

+ 类名的成员属性