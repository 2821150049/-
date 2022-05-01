# day02（用户权限、VI、服务器）

### 一、用户权限

1. **查看当前用户：whoami**

![1](img\1.png)

2. **查看登录用户：who**

![2](img\2.png)

2. **查看用户信息：w -l 用户名**

4. **退出超级管理员模式：exit**

> 当在超级管理员界面时，退出超级管理员
>
> 当在普通用户时，是退出中端

![3](img\3.png)

5. **进入超级管理员：su**

```C
su  //进入超级用户
su user //进入别的用户空间
```

6. **创建用户组：groupadd、删除用户组：groupdel**

```C
groupadd 组名//创建
groupdel 组名//删除
注意：必须在超级管理员状态下才能创建组
```

7. **换组：usermod**

```C
usermod -g 组名 用户名
```

8. **非超级管理员状态创建组和删除组和换组**

```C
sudo groupadd 组名  //创建组
sudo groupdel 组名  //删除组
sudo usermod -g 组名 用户名  //换组
//只是开通了很小的权限
```

![4](img\4.png)

![5](img\5.png)

9. **添加用户账号：useradd**

```C
-d //如果系统不使用该参数，将会自动在/home目录下建立与用户名同名目录为主目录
-m //自动建立目录
-g //指定组名称
useradd -d 目录 用户名 -g 组名 -m
```

![6](img\6.png)

10. **删除用户：userdel**

```C
userdel user（用户名）
userdel -r user //删除用户同时删除用户主目录
```

11. **查看用户登录情况：last**

12. **修改文件权限：chmod**

```C
u //user表示文件的所有者
g //group  用户组
o //other  表示其他以外的人
a //all  表示三者皆是
+ //表示加权限
- //表示减权限
= //设定权限（原有权限全部剥夺）
//目录的权限也可以修改
chmod 用户类型 +|-|= 
```

![7](img\7.png)

![8](img\8.png)

13. **修改文件的所有者：chown**

```C 
sudo chown user test.txt//将文件权限转移
```

14. **修改文件的所属组：chgrp**

> 和usermod一样
>
> 需要进入超级用户

15. **系统管理**
    1. 查看当前日历：cal
    2. 显示时间：date
    3. 查看进程：ps
    4. 动态显示进程：top
    5. 终止进程：kill     
    6. **后台运行：&(ctrl+z)、jobs（查看后台）、fg(唤醒)**
    7. 重启：shutdown    -h 时间，表示关机的时间，-r 会给用户提示
    8. 关机：init 0 开机：init 6
    9. 检测磁盘空间：sudo df -m
    10. 检测目录占用空间：sudo du
    11. 格式化：mkfs
    12. 软件的安装：rpm
    13. 查看网卡信息：ifconfig
    14. 