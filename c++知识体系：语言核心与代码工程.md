>该篇文章结构来着腾讯内部学习平台，但内容均为自己整理而来

# ✧C++知识体系

为便于快速复习C++语言，本文梳理了C++的知识体系，针对C++的重点和难点做了细致说明，同时给出了可运行的源代码，笔者一直以为通过源代码来学习知识点，是掌握一门语言最快的方式。

C++知识体系的搭建基于笔者过往的编程经验，而具体的知识点则参考了知乎上很多优秀文章，所有参考文章都附上了对应链接。

>关于C++的语言核心：  
✧ 新特性：使用新特性有助于简化代码，提高编程效率。例如，一个auto关键字，合理使用可以大大降低大脑和手指的负担，大脑不用记住太多东西， 手指也可以少敲很多代码，体会一下这行代码：for(auto &it : vec) { ... }  
✧ 面向对象：继承/多态/运算符重载是对象对象的核心特征，IOStream作为官方库标准库，是使用面向对象的典范  
✧ 泛型编程：基于template的编程，可能是C++最强大的地方，这是一种和面向对象完全不同的思维方式，STL是使用泛型编程的典范  
✧ 第三方库：编程语言要想发挥巨大作用，必须依赖第三方库，本文重点在语言内核上，对第三方库不做过多介绍
关于C++工程化：主要涉及代码构建，单元测试，代码调试，编程环境IDE

![c++01](/res/c++01.jpeg.webp)

# ✧ 关于学习方法
>作为程序员，编程语言不仅仅是工具，更是饭碗，须勤学苦练，谈几点笔者的看法:  
✧ 每隔两三年学习一门新语言，指望一门语言就能包打天下的时代已经过去了，新生语言在不断蚕食既有语言的地盘，要想不被淘汰，就得紧跟趋势。  
✧ 笔者都会什么语言？熟练使用能够端上饭碗的语言有C++/Python/Golang/shell；学过一年以上能够把该语言核心教程里的代码全部跑通的有：PHP/Javascrip/html/css；通读过该语言核心教程并理解其核心思维的有：java/perl/ruby。  
✧ 程序员之上是架构师，有扎实编程功底，有良好代码品味的架构师才是货真价实的，否则就是花架子，talk is cheap。

![c++02](/res/c++02.webp)

# 1. C++新特性（常用）
>C++11是C++发展的一个分水岭，从此C++进入了所谓的“现代C++”阶段，往后C++14/17/20持续发展。  
在腾讯内部，C++的主战场，比如微信后台/游戏后台，笔者咨询过相关部门的资深C++开发同学，除了一些历史遗留代码，新系统的开发一般都用现代C++。  
就C++具体版本而言，在生产环境中主要还是C++11，例如在微信后台生产环境中gcc的版本是：gcc version 7.5.0 (GCC) ，笔者所在部门腾讯视频，云开发机默认是gcc (GCC) 4.8.5 (Red Hat 4.8.5-39)（注：截止2023.7）。  

这一节对C++常用的新特性做简明扼要的介绍：
![c++03](/res/c++03.webp)

参考： https://www .zhihu.com/pub/reader/12

## 1.1. auto&decltype

auto：变量类型推断 
auto可以让编译器在编译器就推导出变量的类型，可以通过=右边的类型推导出变量的类型  
总结一下auto的限制:  

    auto的使用必须马上初始化，否则无法推导出类型  
    auto在一行定义多个变量时，各个变量的推导不能产生二义性，否则编译失败  
    auto不能用作函数参数  
    在类中auto不能用作非静态成员变量  
    auto不能定义数组，可以定义指针  
    auto无法推导出模板参数  

decltype：用于表达式类型推断，这里只用于编译器分析分析表达式的类型，表达式实际不会进行运算
```
const int ci = 0, &cj = ci;
// x的类型是const int
decltype(ci) x = 0;
// y的类型是const int &
decltype(cj) y = x;
```

## 1.2 for range
基于范围的for循环,这里比较简单，直接上代码
```
std::vector<int> arr(10,0);
for(auto n : arr)
{
    std::cout << n << std::endl;
}
```
## 1.3 function&bind&lambda
> function和bind多用于回调函数
std::function 快速创建一个函数对象
```
# include <iostream>
# include <functional>

typedef std::function<int(int, int)> comfun;

// 普通函数
int add(int a, int b) { return a + b; }

// lambda表达式
auto mod = [](int a, int b){ return a % b; };

// 函数对象类
struct divide{
    int operator()(int denominator, int divisor){
        return denominator/divisor;
    }
};

int main(){
	comfun a = add;
	comfun b = mod;
	comfun c = divide();
    std::cout << a(5, 3) << std::endl;
    std::cout << b(5, 3) << std::endl;
    std::cout << c(5, 3) << std::endl;
}

```
std::bind  绑定函数参数 ，直接上代码，简单易懂
```
void fun_1(int x,int y,int z) {
    std::cout << "print: x = " << x << ", y = " << y << ", z = " << z << std::endl;
}

int mian(){
    auto f1 = std::bind(fun_1, 1, 2, 3); 					//表示绑定函数 fun 的第一，二，三个参数值为： 1 2 3
    f1(); 													//print: x=1,y=2,z=3

    auto f2 = std::bind(fun_1, std::placeholders::_1, std::placeholders::_2, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f2 的第一，二个参数指定
    f2(1, 2);												//print: x=1,y=2,z=3

    auto f3 = std::bind(fun_1, std::placeholders::_2, std::placeholders::_1, 3);
    //表示绑定函数 fun 的第三个参数为 3，而fun 的第一，二个参数分别由调用 f3 的第二，一个参数指定
    //注意： f2  和  f3 的区别。
    f3(1, 2);												//print: x=2,y=1,z=3
}
```
lambda 创建匿名函数,本人经常使用在需要零时绑定函数的时候，QT里面用的最多
>这里贴一张图  

![c++01](/res/c++04.webp)

## 1.4 smart pointer(智能指针)
std::auto_ptr(已弃用)  
std::unique_ptr
std::shared_ptr 
std::~~weak_ptr~~
## 1.5 explicit与default与delete
explicit : 只能显式构造，禁止隐式构造
default ：声明构造函数为默认构造函数
delete ：禁止对象的拷贝与赋值（std::unqiye_ptr就是通过delete修饰来禁止对象的拷贝的）
## 1.6 右值引用与移动构造函数  
这里直接贴个链接
(https://zhuanlan.zhihu.com/p/137662465)

## 1.7 委托构造与继承构造 
![c++03](/res/c++05.webp)
![c++03](/res/c++06.webp)
## 1.8 random
## 1.9 to_string()函数
## 1.10 cstdint
>我giao，刚开始不认识这个头文件，搜了一下发现是固定宽带的整数类型的定义,熟悉的老朋友了

定义了以下整数类型：   
    
    int8_t：8位有符号整数  
    uint8_t：8位无符号整数  
    int16_t：16位有符号整数  
    uint16_t：16位无符号整数  
    int32_t：32位有符号整数   
    uint32_t：32位无符号整数   
    int64_t：64位有符号整数  
    uint64_t：64位无符号整数  
# 2. 面向对象
## 2.1 对象创建与内存管理
### new和malloc
### delete和delete[]
### volatile和mutable

## 2.2 多继承与内存布局
## 2.3 虚函数与纯虚函数
## 2.4 运算符重载 
## 2.5 访问控制  

# 3. template 模板
## 3.1. 函数模板
## 3.2. 类模板
## 3.3. 可变参数
## 3.4. typename与class
## 3.5. STL中的模板

泛型编程，C++最强大的地方，也是最复杂的地方
基于模版的编程，主要用于程序库的编写，例如STL
3.6. 元编程

关于元编程，主要用于编写程序库，实际工程使用较少

# 4. STL （泛型编程典范）
## 4.1 容器
## 4.2 算法
## 4.3 迭代器
## 4.4 STL使用介绍

# 5. IO流（面向对象典范）
## 5.1 iostream 
## 5.2 frtream
## 5.3 stringstream 

# 6. 代码构建
## 6.1 选择什么工具
## 6.2 make和makefile
## 6.3 cmake与CMakeLists.txt
## 6.4 bazel与BUILE
## 6.5 tx的工程实践

# 7. 单元测试
## 7.1 单测概念
## 7.2 单测框架
## 7.3 单测实战

# 8. 代码调试
## 8.1 gdb
## 8.2 通用方法

# 9. 工具链IDE
## 9.1 Vscode
## 9.2 Git与Github
## 9.3 Vim