> 将花费两天时间重学c++基础,简单的地方就不做记录了一笔带过

# 几种重要的关键字
## const
## volatile
## restrict
## mutable
## static
## thread_local
## register
## auto
## decltype
## extern
## define家族
## extern “C”
## delect

# 命名空间
在C/C++中，变量、函数和类都是大量存在的，这些变量、函数和类的名称都将作用于全局作用域中，可能会导致很多命名冲突。  
使用命名空间的目的就是对标识符和名称进行本地化，以避免命名冲突或名字污染
## 命名空间的普通定义
> 定义命名空间，需要使用到 namespace 关键字，后面跟命名空间的名字，然后接一对{}即可
```
namespace SPACENAME
{
    int a;
	int b;
}
//使用方法
SPACENAME::a;
SPACENAME::b;
```
## 命名空间的嵌套定义
```
//命名空间的嵌套定义
namespace SPACENAME1 //定义一个名为N1的命名空间
{
	int a;
	int b;
	namespace SPACENAME2 //嵌套定义另一个名为N2的命名空间
	{
		int c;
		int d;
	}
}
//使用方法
SPACENAME1::SPACENAME2::c;
SPACENAME1::SPACENAME2::d;
```
## 使用using将命名空间中的成员引入
> 过“using 命名空间名称::命名空间成员”的方式将命名空间中指定的成员引入。这样一来，在该语句之后的代码中就可以直接使用引入的成员变量
```
//使用using将命名空间中的成员引入
#include <stdio.h>
namespace N
{
	int a;
	double b;
}
using N::a;//将命名空间中的成员a引入
int main()
{
	a = 10;//将命名空间中的成员a赋值为10
	printf("%d\n", a);//打印命名空间中的成员a
    printf("%d\n", N::a);//打印命名空间中的成员a
	return 0;
}
```
## 使用using namespace 命名空间名称引入
> 通过”using namespace 命名空间名称“将命名空间中的全部成员引入。这样一来，在该语句之后的代码中就可以直接使用该命名空间内的全部成员了
```
//使用using namespace 命名空间名称引入
#include <stdio.h>
namespace N
{
	int a;
	double b;
}
using namespace N;//将命名空间N的所有成员引入
int main()
{
	a = 10;//将命名空间中的成员a赋值为10
	printf("%d\n", a);//打印命名空间中的成员a
	return 0;
}

```
# 函数
## 函数声明
> 函数声明，也称为函数原型，是在函数实际定义之前向编译器声明函数的存在.  
> 函数声明会告诉编译器函数名称及如何调用函数  
函数声明一般包含以下几部分：
```
return_type function_name( parameter list );
```
## 函数定义
C++ 中的函数定义的一般形式如下：
```
return_type function_name( parameter list )
{
   body of the function
}
```
## 函数参数
### 传递参数的方式
1、值传递  
2、引用传递  
3、指针传递
### 缺省函数参数 
> 缺省参数是指在声明或定义函数时，为函数的参数指定一个默认值。在调用该函数时，如果没有指定实参则采用该默认值，否则使用指定的实参。  
1、全缺省参数  
>即函数的全部形参都设置为缺省参数  
```
void Print(int a = 10, int b = 20, int c = 30);
```
2、半缺省参数  
>即函数的参数不全为缺省参数  
```  
void Print(int a, int b, int c = 30);
```  
3、注意事项  
（1）半缺省参数必须从右往左依次给出，不能间隔着给。  
```
void printNum(int a,int b=1,int c=2);
```
（2）缺省参数不能在函数声明和定义中同时出现  
（3）缺省值必须是常量或者全局变量  
## 函数重载
### 概念
函数重载允许在同一作用域中定义多个具有相同名称但参数不同的函数。C++ 通过参数的类型、数量和顺序来区分这些函数  
```
int Add(int x, int y)
{
	return x + y;
}
double Add(double x, double y)
{
	return x + y;
}
```
### 原理  
C++在进行编译符号汇总时，对函数的名字修饰做了改动，函数汇总出的符号不再单单是函数的函数名，而是通过其参数的类型和个数以及顺序等信息汇总出一个符号，这样一来，就算是函数名相同的函数，只要其参数的类型或参数的个数或参数的顺序不同，那么汇总出来的符号也就不同了  
## 内联函数
### 定义
联函数的定义与普通函数基本相同,只是在函数定义前加上关键字 inline。
```
inline void print(char *s)
{
    printf("%s", s);
}
```
### 内联函数的目的
1. 代替部分宏定义
    · 宏是预处理指令，在预处理的时候把所有的宏名用宏体来替换；内联函数是函数，在编译阶段把所有调用内联函数的地方把内联函数插入  
    · 宏没有类型检查，无论对还是错都是直接替换；而内联函数在编译时进行安全检查​  
    · 宏的编写有很多限制，例如只能写一行，不能使用return控制流程等  
    · 对于C++ 而言，使用宏代码还有另一种缺点：无法操作类的私有数据成员  
2. 代替普通函数提高运行效率
    普通函数频繁调用的过程消耗栈空间。程序在执行一个函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都压入栈中，然后才能执行函数体中的代码；函数体中的代码执行完毕后还要清理现场，将之前压入栈中的数据都出栈，才能接着执行函数调用位置以后的代码。  
    在系统下，栈空间是有限的，假如频繁大量的使用就会造成因栈空间不足所造成的程式出错的问题。
### 隐式内联和显式内联
1. 隐式内联
   C++中在类内定义的所有函数都自动称为内联函数
2. 显式内联
   需要使用inline关键字，在类外定义的函数，如果想变为内联函数都需要加inline关键字
### 问题和思考
1. 加入inline后函数一定会展开吗
   不一定，使用内联inline关键字修饰函数只是一种提示，编译器不一定认。
2. 如何要求编译器展开内联函数
   （1）编译器开优化：只有在编译器开启优化选项的时候，比如gcc -O2。  
   （2）使用attribute属性：static inline __attribute__((always_inline)) int add_i(int a,int b)；  
   （3）使用auto_inline：#pragma auto_inline(on/off)，当使用#pragma auto_inline(off)指令时，会关闭对函数的inline处理，这时即使在函数前面加了inline指令，也不会对函数进行内联处理。  
上述操作都仅仅是对编译器提出内联的建议，最终是否进行内联由编译器自己决定  

### 使用注意事项
1. 内联函数不能包括复杂的控制语句，如循环语句和switch语句；
2. 内联函数不能包括复杂的控制语句，如循环语句和switch语句；
3. 只将规模很小（一般5个语句一下）而使用频繁的函数声明为内联函数。在函数规模很小的情况下，函数调用的时间开销可能相当于甚至超过执行函数本身的时间，把它定义为内联函数，可大大减少程序运行时间。
# 指针
> 指针是一个变量，其值为另一个变量的地址，即，内存位置的直接地址。
## 传统指针
声明：
```
type *var-name;
int    *ip;    /* 一个整型的指针 */
double *dp;    /* 一个 double 型的指针 */
float  *fp;    /* 一个浮点型的指针 */
char   *ch;    /* 一个字符型的指针 */
```
指针数组(指针的数组);
数组指针（数组的指针）;
char * 和 char[];
const int * p;
int * const p;
const int * const p;
void*是不能隐式转换成其他类型的指针的;
## 指针空值
NULL和nullptr  
1. NULL:
在c++中的处理为：
```
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
```  
可见，在C++中，NULL实际上是0  
注意：用NULL代替0表示空指针在函数重载时会出现问题
```
#include <iostream>
using namespace std;
 
void func(void* i)
{
	cout << "func1" << endl;
}
 
void func(int i)
{
	cout << "func2" << endl;
}
 
void main(int argc,char* argv[])
{
	func(NULL);
	func(nullptr);
	getchar();
}
```
2. nullptr
为解决NULL代指空指针存在的二义性问题，在C++11版本(2011年发布)中特意引入了nullptr这一新的关键字来代指空指针

## 野指针和空悬指针
野指针：野指针是指尚未初始化的指针，既不指向合法的内存空间,也没有使用 NULL/nullptr 初始化指针  
空悬指针：悬空指针是指 指针指向的内存空间已被释放或不再有效
## 智能指针
### 最常用的智能指针
1. shared_ptr
> 共享式指针，同一时刻可以有多个指针指向同一个对象
2. weak_ptr
3. unique_ptr
4. auto_ptr(已弃用)
### boost库中的指针
1. boost::scoped_ptr
2. boost::scoped_array
3. boost::shared_ptr
4. boost::shared_array
5. boost::weak_ptr
6. boost::intrusive_ptr
7. boost::ptr_vector
# 引用
引用变量是一个别名，也就是说，它是某个已存在变量的另一个名字。一旦把引用初始化为某个变量，就可以使用该引用名称或变量名称来指向变量。
说白了就是一个const指针
```
int main() {
   int a = 10;
   int *b=&a;
   int * &c = b;
   printf("%p\n",b);
   printf("%p\n",c);
   printf("%p\n",&c);  
}
```
· 不存在空引用。引用必须连接到一块合法的内存
· 一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象
· 引用必须在创建时被初始化。指针可以在任何时间被初始化

# 类
## 虚函数与纯虚函数
1. 虚函数
    虚函数是在基类中使用virtual关键字声明的函数，可以在派生类中被重写。可以用来实现多态。其核心目的是通过基类访问派生类定义的函数。

2. 纯虚函数
   
3. 虚函数表

4. 虚函数调用原理

## 构造函数
## 析构函数
## this指针与enable_shared_from_this
## 拷贝赋值函数
## 静态成员变量
## 静态类
## 深拷贝与浅拷贝
## 友元
## 重写
## 重载
## 运算符重载
## 类的实例化
## 类对象模型
## 初始化列表
## 内部类

# 结构体
在c++里结构体与类的区别不大，唯一区别就是结构体的默认权限是public  
# 接口
# 继承
# 多态
# 异常
# 类型转换
# c++内存管理
# STL
## 算法
## 容器
## 迭代器
## 空间配置器
# c++ 11
## 右值引用与移动语义
## lambad表达式
## 包装器
