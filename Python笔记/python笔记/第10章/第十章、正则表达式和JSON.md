# 第十章、正则表达式和JSON

[TOC]

## 一、正则表达式

1. 正则表达式是一个**特殊的字符序列**，一个字符串是否与我们所设定的这样的字符序列，相匹配，快速检索文本‘实现一些替换文本的操作

   + 检测一串数字是否是电话号码
   + 检测一个字符是否是email
   + 把一个文本了指定的单词替换为另一个单词

2. 内置函数优先选择来解决字符串的问题

   + ```python
     a = "c|c++|java|c#|python|javascript"
     
     print(a.index("python")>-1)
     print("python" in a)
     # 结果：
     True
     True
     ```

3. `re`[^1]

   1. `findall("正则表达式",数据)`

      + ```python
        import re
        a = "c|c++|java|c#|python|javascript"
        # 正则表达式
        r = re.findall("python",a)
        print(r)
        # 结果：
        ['python']
        
        r = re.findall("PHP",a)
        print(r)
        # 结果：
        []
        ```

      + *常量是没有规则的，正则表达式最重要的就是规则*

   2. 元字符与普通字符

      + `\d`[^2]

      + ```python
        import re
        
        a = "c0c++7java8c#9python6javascript"
        # 将数字全部提取出来
        r = re.findall("\d",a)
        print(r)
        # 结果：
        ['0', '7', '8', '9', '6']
        ```

      + > `python`  普通字符
        >
        > `\d`元字符：匹配一个数字字符
        >
        > `\D`：匹配一个非数字字符

      + ```python
        import re
        
        a = "c0c++7java8c#9python6javascript"
        
        # 将数字全部提取出来
        r = re.findall("\D",a)
        print(r)
        # 结果：
        ['c', 'c', '+', '+', 'j', 'a', 'v', 'a', 'c', '#', 'p', 'y', 't', 'h', 'o', 'n', 'j', 'a', 'v', 'a', 's', 'c', 'r', 'i', 'p', 't']
        ```

   3. 字符集：`[字符]`匹配某一个字符，字符与字符之间是或的关系

      + ```python
        # 字符集
        import re
        s = "abc,acc,adc,aec,afc,ahc"
        # 找一个中间字符是c或者是f的单词
        r = re.findall("a[cf]c",s)
        print(r)
        # 结果：a\c是用来定界的
        ['acc', 'afc']
        ```

      + `[^字符]`取反的操作

      + ```python
        # 字符集
        import re
        s = "abc,acc,adc,aec,afc,ahc"
        # 找一个中间字符是c或者是f的单词
        r = re.findall("a[^cf]c",s)
        print(r)
        # 结果：
        ['abc', 'adc', 'aec', 'ahc']
        ```

      + `[字符-字符]`取某一段字符

      + ```python
        # 字符集
        import re
        s = "abc,acc,adc,aec,afc,ahc"
        # 找一个中间字符是c或者是f的单词
        r = re.findall("a[c-f]c",s)
        print(r)
        # 结果：
        ['acc', 'adc', 'aec', 'afc'
        ```

   4. 概括字符集

      + `\d`、`\D`

      + ```python
        # 字符集
        import re
        s = "vbialv51d46ia856lgv"
        
        r = re.findall("\d",s)
        print(r)
        r = re.findall("[0-9]",s)
        print(r)
        # 结果：
        ['5', '1', '4', '6', '8', '5', '6']
        ['5', '1', '4', '6', '8', '5', '6']
        ```

      + `\w`匹配字母和数字、`\W`匹配非字母数字

      + ```python
        # 字符集
        import re
        s = "vbialv51d/46ia85;6l'gv"
        
        r = re.findall("\w",s)
        print(r)
        # 结果：
        ['v', 'b', 'i', 'a', 'l', 'v', '5', '1', 'd', '4', '6', 'i', 'a', '8', '5', '6', 'l', 'g', 'v']
        ```

      + `[A-Za-z0-9_]`

      + ```python
        # 字符集
        import re
        s = "vbialv51d/46ia85;6l'gv"
        
        r = re.findall("[A-Za-z0-9_]",s)
        print(r)
        # 结果：
        ['v', 'b', 'i', 'a', 'l', 'v', '5', '1', 'd', '4', '6', 'i', 'a', '8', '5', '6', 'l', 'g', 'v']
        ```

      + `\s`匹配空白字符、`\S`非空白字符

      + ```python
        # 字符集
        import re
        s = "vbial v51\td/46\n  ia\r85;6l'gv"
        
        r = re.findall("\s",s)
        print(r)
        # 运行结果：
        [' ', '\t', '\n', ' ', ' ', '\r']
        ```

   5. 数量级：表示前面的字符的个数

      + `{min,max}`：重复前面的正则表达式

      + ```python
        # 字符集
        import re
        s = "c|c++354|java3453|c#|3453python|3453javascript"
        
        r = re.findall("[a-z+#]{1,10}",s)
        print(r)
        # 结果：
        ['c', 'c++', 'java', 'c#', 'python', 'javascript']
        ```

   6. 贪婪与非贪婪：为什么匹配到3个就能结束还要继续匹配

      + 默认状态下是贪婪方式匹配

      + 非贪婪的表示方式：`{min,max}?`

      + ```python
        # 字符集
        import re
        s = "c|c++354|java3453|c#|3453python|3453javascript"
        
        r = re.findall("[a-z+#]{3,10}?",s)
        print(r)
        # 结果：
        ['c++', 'jav', 'pyt', 'hon', 'jav', 'asc', 'rip']
        ```

   7. 匹配0次1次或者无限次

      + `*`匹配星号前面的字符0次或者无限多次

      + ```python
        # 字符集
        import re
        s = "c|c++354pytho|java3453|c#|3453python|3453pythonnjavascript"
        
        r = re.findall("python*",s)
        print(r)
        # 结果：
        ['pytho', 'python', 'pythonn']
        ```

      + `+`匹配星号前面的字符1次或者无限多次

      + ```python
        import re
        s = "c|c++354pytho|pyjavan3453|c#|3453python|3453pythonnn"
        
        r = re.findall("python+",s)
        print(r)
        # 结果：
        ['python', 'pythonnn']
        ```

      + `?`匹配星号前面的字符1次或者0次

      + ```python
        # 字符集
        import re
        s = "c|c++354pytho|pyjavan3python|3453pythonnn"
        
        r = re.findall("python?",s)
        print(r)
        # 结果：
        ['pytho', 'python', 'python']
        ```

   8. 边界匹配符

      + `^\d{4,8}$`  `^`从第一个开始匹配  `$`从最后一个开始匹配

      + ```python
        # 边界匹配
        import re
        qq = "100000001"
        
        r = re.findall('^\d{4,8}$',qq)
        print(r)
        # 结果：
        []
        ```

      + ```python
        # 边界匹配
        import re
        qq = "100000001"
        r = re.findall('^000',qq)
        print(r)
        # 结果：
        []
        r = re.findall('000$',qq)
        print(r)
        # 结果：
        []
        ```

   9. 组

      + `()`括号扩起来的叫组、一个正则表达式中不止有一个组、可以有多个，**小括号表示每个字符之间的关系是且的关系**`[]`*每个变量之间是或的关系*

      + ```python
        # 组
        import re
        a = "PythonPythonPythonPythonPythonJS"
        r = re.findall('(Python){3}(JS)',a)
        print(r)
        # 结果
        [('Python', 'JS')]
        ```

   10. `findall`的第三个参数，模式参数，可以同时使用多个模式用`|`连接

       + ```python
         # 第三参数
         import re
         a = "c|c++|java|c#|python|javascript"
         r = re.findall('C#',a,re.I | re.S)
         print(r)
         # 结果：
         ['c#']
         ```

4. `re.sub(正则表达式,替换的数据,查找的数据,count指替换次数)`正则替换，count = 0是表示只要有就会替换

   + ```python
     # sub
     import re
     a = "c|c++|java|c#|python|javascript"
     r = re.sub("c#","go",a)
     print(r)
     # 结果：
     c|c++|java|go|python|javascript
     ```

   + 强大的地方在与，第二个参数可以时函数

   + ```python
     # sub
     import re
     a = "c|c++|c#|java|c#|python|c#|javascript"
     def convert(value):
         print(value)
         # return "--"+value+"--"
     r = re.sub("c#",convert,a)
     print(r)
     # 结果：
     <re.Match object; span=(6, 8), match='c#'>
     <re.Match object; span=(14, 16), match='c#'>
     <re.Match object; span=(24, 26), match='c#'>
     c|c++||java||python||javascript
     # sub
     import re
     a = "c|c++|java|c#|python|javascript"
     def convert(value):
         return "csacsvaw"
     r = re.sub("c#",convert,a)
     print(r)
     # 结果：
     c|c++|java|csacsvaw|python|javascript
     # sub
     import re
     a = "c|c++|c#|java|c#|python|c#|javascript"
     def convert(value):
         matched = value.group()
         return "--"+matched+"--"
     r = re.sub("c#",convert,a)
     print(r)
     # 结果：
     c|c++|--c#--|java|--c#--|python|--c#--|javascript
     ```

5. 把函数当做参数传递

   + ```python
     # sub
     import re
     a = "A8C3721D86"
     def convert(value):
         matched = value.group()
         if "9">= matched > "6":
             return "9"
         elif "0" <= matched < "3":
             return "1"
     r = re.sub("[1-9]",convert,a)
     print(r)
     # 结果：
     A9C911D9
     ```

6. `match和search`用法和`findall`一样

   + match是从首字母开始
   + search是看所有数据
   + 返回值不一样

7. `group()`：分组、在于分组的匹配

   + 0：永远是全部值

   + 1：返回组值

   + ```python
     import re
     s = "life is short,i use python"
     r = re.search("life (.*) python",s)
     print(r.group(1))
     # 结果：
     is short,i use
     ```

   + `groups()`：返回组值

8. 学习方法：

   1. 常用的正则表达式，可以用别人写好的

## 二、JSON

1. JSON是一种轻量级的数据**交换格式**

   1. 字符串是JSON的表现形式
   2. 符合JSON格式的字符串叫做JSON字符串
   3. *跨语言交换数据*

2. 反序列化：JSON原先拿到的数据就是字符串

   + `json`包：JSON专用包

   + `loads(json字符串)`：将json数据转换成语言所支持的一种数据类型，python中为字典类型

   + ```python
     import json
     # JSON
     json_str = '''{"name":"qiyue", "age":"18"}'''
     student = json.loads(json_str)
     print(student["name"])
     # 运行结果：
     qiyue
     ```

   + ```python
     # 数组时
     import json
     json_str = '''[{"name1":"qiyue1", "age1":"15"}, {"name":"qiyue", "age":"18"}]'''
     student = json.loads(json_str)
     print(type(student))
     print(student)
     # 结果：
     <class 'list'>
     [{'name1': 'qiyue1', 'age1': '15'}, {'name': 'qiyue', 'age': '18'}]
     ```

   + 解析过程：反序列化。

3. 序列化：

   + `dumps(object)`：序列化方法

   + ```python
     # JSON
     import json
     
     student = [
                     {'name1': 'qiyue1', 'age1': '15'}, 
                     {'name': 'qiyue', 'age': '18'}
               ]
     json_str = json.dumps(student)
     print(type(json_str))
     print(json_str)
     # 结果：
     <class 'str'>
     [{"name1": "qiyue1", "age1": "15"}, {"name": "qiyue", "age": "18"}]
     ```
|  json  | python |
| :----: | :----: |
| object |  dict  |
| array  |  list  |
| string |  str   |
| number |  int   |
| number | float  |
|  true  |  True  |
| false  | False  |
|  null  |  None  |

4. JSON对象、JSON、JSON字符串



[^1]:  模块
[^2]:表示数字1 - 9