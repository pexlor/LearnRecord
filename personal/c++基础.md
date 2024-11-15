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

## default

## override

## final

## explicit

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
> 函数声明一般包含以下几部分：

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
> 1、全缺省参数
> 即函数的全部形参都设置为缺省参数

```
void Print(int a = 10, int b = 20, int c = 30);
```

2、半缺省参数

> 即函数的参数不全为缺省参数

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
   · 宏是预处理指令，在预处理的时候把所有的宏名用宏体来替换；内联函数是函数，在编译阶段把所有调用内联函数的地方把内联函数插入· 宏没有类型检查，无论对还是错都是直接替换；而内联函数在编译时进行安全检查· 宏的编写有很多限制，例如只能写一行，不能使用return控制流程等· 对于C++ 而言，使用宏代码还有另一种缺点：无法操作类的私有数据成员
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
> （1）创建方式

```

```

2. unique_ptr

> 独占式指针

3. weak_ptr
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
上面说的都是普通引用又称左值引用，下面看看右值引用：
通过&& 声明，同时：
右值引用只能绑定到一个右值，不能绑定到左值；
右值引用可以通过std::move() 将一个左值转换成右值引用

```
int a=0;
int&& tmp=a;   //error,不能引用左值
int&& tmp2=0;  //correct
int&& tmp3 = move(a); //correct
```

# 类

## 类权限

## 虚函数与纯虚函数

1. 虚函数
   虚函数是在基类中使用virtual关键字声明的函数，可以在派生类中被重写。可以用来实现多态。其核心目的是通过基类访问派生类定义的函数。

```
virtual void Test();
```

2. 纯虚函数
   纯虚函数是指在基类中声明但不实现的虚函数，它的声明使用了 = 0 的语法。一个包含纯虚函数的类称为抽象类，不能直接实例化，必须由派生类实现所有纯虚函数后才能实例化对象。

```
virtual void Test() = 0;
```

3. 虚函数表
   在C++中，虚函数表（通常称为vtable）是实现类多态性的核心机制。虚函数表是一个指针数组，每个指针指向类的一个虚函数实现。这个表的存在使得在运行时可以根据对象的实际类型来调用相应的函数，从而实现了多态。(1)虚函数表的创建与维护
   a.虚函数的引入：当类中声明了至少一个虚函数时，编译器为该类生成一个虚函数表。此表在类的每个对象中都有一个指针指向它（称为虚指针，vptr）。这个虚指针是对象的隐式成员，位于对象内存布局的前端。b.如果一个类从另一个类继承，并且继承的类有虚函数，派生类会继承这个虚函数表。如果派生类覆写了任何虚函数，相应的虚函数表条目会更新为指向派生类中的函数实现。c.纯虚函数和抽象类：纯虚函数是一种特殊的虚函数，它在基类中没有实现，必须在派生类中被覆写。类中如果存在纯虚函数，该类成为抽象类，不能实例化对象。纯虚函数在虚函数表中通常用特殊标记（如NULL指针）表示，这防止了基类的纯虚函数被直接调用。
   (2)虚函数表的运行时开销
   a.内存开销：每个对象需要额外存储一个指向虚函数表的指针，这增加了对象的大小。b.执行开销：调用虚函数时，需要先通过虚指针访问虚函数表，然后找到对应的函数指针，最后执行函数。这个过程比直接函数调用要慢，因为涉及到多个间接跳转。
4. 虚函数与纯虚函数的继承与执行
   (1)虚函数的继承a. 覆写虚函数：当派生类继承基类时，它可以选择覆写基类中的虚函数。通过覆写，派生类提供了虚函数的新实现，这一实现会在派生类的对象通过基类指针或引用调用时执行。
   b. 虚函数表更新：如果派生类覆写了基类的虚函数，派生类的虚函数表中相应的条目将被更新为指向派生类的新函数。这保证了当通过基类的接口调用虚函数时，能够执行到派生类中定义的行为。
   c. 动态绑定：虚函数的调用是动态绑定的，这意味着函数的选择是在运行时根据对象的实际类型进行的。这是实现运行时多态的核心。
   (2)纯虚函数的继承和基类的虚函数表存在的理由a. 抽象接口：纯虚函数通常用来定义一个接口，这个接口在基类中没有具体的实现，必须由派生类来提供。b. 强制覆写：通过纯虚函数，基类可以强制派生类提供特定函数的实现。如果派生类没有实现所有的纯虚函数，它也将成为抽象类，无法实例化。c. 多层继承中的纯虚函数：在多层继承结构中，一个中间类可能实现了其基类的纯虚函数，而这个实现可以被更下一层的派生类继承或再次覆写。这为复杂的继承体系提供了灵活性和扩展性。d. 接口定义：基类通过纯虚函数定义了一个接口，这个接口必须由任何非抽象的派生类实现。虚函数表提供了一种机制来确保这些接口在派生类中得到正确实现和调用。e. 派生类的多态性：派生类继承基类的虚函数表，并且可以覆写这些虚函数表中的条目以实现具体功能。如果派生类没有覆写某个纯虚函数，则该派生类也会变为抽象类。f. 保持结构一致性：在C++的继承体系中，保持虚函数表的一致性对于对象的多态行为至关重要。基类的虚函数表为派生类提供了一个结构框架，即使基类本身不能被实例化。
5. 注意事项
   （1）c++规定，当一个成员函数被声明为虚函数后，其派生类中的同名函数都自动成为虚函数。
   （2）虚函数在子类中可以不声明与定义，但是它在子类中一经声明，就必须要定义。

## 构造函数

### 概念

    一个类的对象被创建的时候，编译系统对象分配内存空间，并自动调用该构造函数，由构造函数完成成员的初始化工作。因此，构造函数的核心作用就是，初始化对象的数据成员

### 特点

（1）名字与类名相同，可以有参数，但是不能有返回值（连void也不行）。

（2）构造函数是在实例化对象时自动执行的，不需要手动调用。

（3）作用是对对象进行初始化工作，如给成员变量赋值等。

（4）如果定义类时没有写构造函数，系统会生成一个默认的无参构造函数，默认构造函数没有参数，不做任何工作。

（5）如果定义了构造函数，系统不再生成默认的无参构造函数.

（6）对象生成时构造函数自动调用，对象一旦生成，不能在其上再次执行构造函数

（7）一个类可以有多个构造函数，为重载关系

### 几种构造函数

（1）默认构造函数
当一个类没有构造函数时，如果满足以下四个条件其中之一，则编译器会为该类自动生成一个默认的构造函数：
    a. 该类含有一个类类型（非内置类型）的成员变量，且该类型含有默认构造函数。
    b. 该类继承自含有默认构造函数的基类。
    c. 该类继承或声明了虚函数。
    d. 该类含有虚基类。
一是定义一个无参的构造函数，二是定义所有参数都有默认值的构造函数

```
testClass();                    /* 默认构造函数 */
testClass(int a=10,char b='c');    /* 默认构造函数 */
```

（2）普通构造函数

```
Student(int num，int age）;//有参数
Student(int num，int age = 10）;//有缺省参数
```

（3）拷贝构造函数
a. 默认拷贝构造函数
	当一个类没有拷贝构造函数时，如果满足以下四个条件其中之一，则编译器会为该类自动生成一个默认的拷贝构造函数：
	该类含有一个类类型（非内置类型）的成员变量，且该类型含有拷贝构造函数。
	该类继承自含有拷贝构造函数的基类。
	该类继承或声明了虚函数。
	该类含有虚基类。
	需要注意的是，默认的拷贝构造函数实现的是浅拷贝。
b. 自定义拷贝构造函数

```
//拷贝构造函数
CExample(const CExample & c)
{
	a=c.a;
	printf("copy constructor is called\n");
}
```

C. 使用条件
1).当用一个对象去初始化同类的另一个对象时，会引发复制构造函数被调用。

```
CExample a;
CExample b(a);//会调用
CExample c = a;//会调用
```

2).如果函数 F 的参数是类 A 的对象，那么当 F 被调用时，类 A 的复制构造函数将被调用。就是值传递时会复制一遍对象这时候就会调用拷贝构造函数

```
void g_fun(CExample c)
{
    cout<<"g_func"<<endl;
}
int main()
{
    g_fun(A);
}

```

3). 如果函数的返冋值是类 A 的对象，则函数返冋时，类 A 的复制构造函数被调用。

```
CExample g_fun()
{
    CExample temp(0);
    return temp;
}
int main()
{
    g_fun();
}
```

（4）转换构造函数
一个构造函数接收一个不同于其类类型的形参，可以视为将其形参转换成类的一个对象。像这样的构造函数称为转换构造函数。
注意这里只能有一个参数
explicit会生成显式类型转换构造函数，此时就必须显式调用转换构造函数

```
class Complex{
	public:
		double real , imag;
		//类型转换构造函数
		Complex(int i){
			std::cout << "IntConstructor called" << std::endl;
			real = i;
			imag = 0;
		}
		Complex(double r, double i){
			real = r;
			imag = i;
		}
};

int main(){
	Complex c1(7,8);
	Complex c2 = 12；//调用类型转换构造函数
	c1 = 9;//调用类型转换构造函数，9被转换为一个临时的Complex对象
	std::cout << c1.real <<","<< c1.imag<<std::endl;
	std::cout << c2.real <<","<< c2.imag<<std::endl;
	return 0 ;
}
```

（5）移动构造函数
a. 什么是移动语义
所谓移动语义，指的就是以移动而非深拷贝的方式初始化含有指针成员的类对象。简单的理解，移动语义指的就是将其他对象（通常是临时对象）拥有的内存资源“移为已用”。
b. 左值和右值

c. 移动构造函数定义和使用

```
class A
{
public:
	A() { cout << "Constructor" << endl; }
	A(const A&) { cout << "Copy Constructor" << endl; }
	A(const A&&) { cout << "Move Constructor" << endl; }
	~A() {}
};

A getA()
{
	A a;
	return a;
}

int main()
{
	A a = getA();// getA()是一个右值
	system("pause");
	return 0;
}

```

### 构造函数调用顺序

基类构造函数：首先会调用基类的构造函数。在创建派生类对象时，系统首先会调用基类的构造函数，然后再调用派生类的构造函数。这个过程从基类向派生类逐级递进。

成员对象的构造函数：如果类中包含成员对象，那么在基类构造函数之后，首先会调用成员对象的构造函数，按它们在类中出现的顺序进行。

派生类构造函数：最后才会调用派生类的构造函数

## 析构函数

在于对象销毁前系统会自动调用，进行一些清理工作

```
格式：~类名(){函数体} --- ~Person(){...}
```

### 虚析构

将析构函数什么为虚函数
虚析构函数的作用：
（1）如果父类的析构函数不加virtual关键字
当父类的析构函数不声明成虚析构函数的时候，当子类继承父类，父类的指针指向子类时，delete掉父类的指针，只调动父类的析构函数，而不调动子类的析构函数。
（2）如果父类的析构函数加virtual关键字
当父类的析构函数声明成虚析构函数的时候，当子类继承父类，父类的指针指向子类时，delete掉父类的指针，先调动子类的析构函数，再调动父类的析构函数。

### 构造函数调用顺序

1. 派生类析构函数：首先调用派生类的析构函数。
2. 成员对象析构函数：然后调用成员对象的析构函数。
3. 基类析构函数：最后调用基类的析构函数。

## this指针与enable_shared_from_this

### this指针

#### 定义

C++中成员变量和成员函数是分开存储的，每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码
那么问题是：这一块代码是如何区分哪个对象调用自己的呢？
C++通过提供特殊的对象指针，this指针，解决上述问题。
this指针指向被调用的成员函数所属的对象

#### 用途

1. 当形参和成员变量同名时，可用this指针来区分
2. 在类的非静态成员函数中返回对象本身，可使用return *this

#### 本质

this指针的本质是一个指针常量：const Type* const pointer;
他储存了调用他的对象的地址，并且不可被修改。这样成员函数才知道自己修改的成员变量是哪个对象的。

#### 其他问题

1. this指针存在哪里？
   其实编译器在生成程序时加入了获取对象首地址的相关代码。并把获取的首地址存放在了寄存器ECX中(VC++编译器是放在ECX中，其它编译器有可能不同)。也就是成员函数的其它参数正常都是存放在栈中。而this指针参数则是存放在寄存器中。
   类的静态成员函数因为没有this指针这个参数，所以类的静态成员函数也就无法调用类的非静态成员变量。
2. this指针可以为空吗？
   可以为空。当我们在调用函数的时候，如果函数内部不需要通过this指向当前对象并对其进行操作时才可以为空(当我们在其中什么都不放或者在里面随便打印一个字符串)；如果调用的函数需要指向当前对象，并进行操作，则会发生错误(空指针引用)。

### enable_shared_from_this

#### 什么是 enable_shared_from_this

enable_shared_from_this 是一个 C++ 标准库中的模板类，提供了一种安全的方式在类的成员函数中创建指向当前对象的 std::shared_ptr。它解决了在对象已经被 std::shared_ptr 管理的情况下，如何在类的成员函数中创建新的 std::shared_ptr 指向同一个对象的问题。

#### 为什么需要 enable_shared_from_this

在 C++ 中，std::shared_ptr 是一种智能指针，用于管理动态分配的对象。它通过引用计数来管理对象的生命周期。当最后一个指向对象的 std::shared_ptr 被销毁时，对象的内存会被自动释放。
如果在一个类的成员函数中，试图创建一个新的 std::shared_ptr 指向当前对象（即使用 this 指针），会导致问题。直接用 this 创建一个新的 std::shared_ptr 会导致两个独立的 std::shared_ptr 管理同一个对象，它们的引用计数彼此不相关，这样会导致对象在第一个 std::shared_ptr 被销毁时被删除，而另一个 std::shared_ptr 变成悬空指针。

#### 如何使用 enable_shared_from_this

为了避免上述问题，C++ 提供了 enable_shared_from_this。当类继承自 enable_shared_from_this 时，可以在类的成员函数中使用 shared_from_this() 方法来安全地获取一个 std::shared_ptr，这个 std::shared_ptr 和管理该对象的原始 std::shared_ptr 共享同一个引用计数。

```
#include <iostream>
#include <memory>

class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    std::shared_ptr<MyClass> getSharedPtr() {
        // 使用 shared_from_this() 获取一个 shared_ptr 指向当前对象
        return shared_from_this();
    }

    void show() {
        std::cout << "MyClass instance" << std::endl;
    }
};
int main() {
    std::shared_ptr<MyClass> p1 = std::make_shared<MyClass>();
    std::shared_ptr<MyClass> p2 = p1->getSharedPtr();

    p1->show();
    p2->show();

    std::cout << "p1 use count: " << p1.use_count() << std::endl; // 输出引用计数
    std::cout << "p2 use count: " << p2.use_count() << std::endl;

    return 0;
}
```

## static成员变量与函数

### static成员变量定义与特性

    static成员变量属于整个类，而不是某个具体的对象。它在类的所有对象之间共享。
    它只在内存中有一份，即使创建了多个对象。
    必须在类外部进行定义和初始化。

### static成员函数定义与特性

    static成员函数不依赖于对象实例，可以通过类名直接调用。
	不能访问非静态成员变量和非静态成员函数，因为它没有 this 指针。

## const成员变量与函数

### const成员变量定义与特性

    const成员变量在对象创建后不能被修改，通常在初始化列表中进行初始化。
	它表示对象的一种固定属性，如对象的标识符、配置参数等。

### const成员函数

    const成员函数承诺不修改对象的状态，即不修改成员变量。
	在函数声明的后面加上 const 关键字。
	const成员函数只能调用其他的 const 成员函数。

```
class MyClass {
    int value;
public:
    MyClass(int v) : value(v) {}
    int getValue() const { return value; }  // const成员函数
    void setValue(int v) { value = v; }  // 非const成员函数
};
```

## 成员变量初始化

### 初始化列表

在对象构造时，成员变量直接通过初始化列表进行初始化。
避免了先调用默认构造函数再赋值的操作，尤其对复杂类型来说，能显著提高效率。(这里就可以少调用一次拷贝构造)

```
class MyClass {
    int x;
    const int y;
    int& ref;
public:
    MyClass(int a, int b, int& r) : x(a), y(b), ref(r) {}  // 使用初始化列表
};
```

### 声明时初始化

### 构造函数初始化

### 初始化顺序

成员变量初始化的顺序为：先进行声明时初始化，然后进行初始化列表初始化，最后进行构造函数初始化
成员变量的初始化顺序仅与其定义顺序相关，与初始化列表顺序无关；而且初始化列表先与构造函数体执行；
当类成员变量在构造函数体中赋值初始化时，初始化的顺序由构造函数体中变量的赋值顺序决定，与其定义顺序无关。

## 深拷贝与浅拷贝

主要是指针的问题

### 浅拷贝

浅拷贝是指拷贝对象时，只复制对象中的基本数据类型，而不复制指针指向的内容。浅拷贝会导致多个对象共享同一块内存，因此修改一个对象的内容可能会影响其他对象。

### 深拷贝

深拷贝是指在拷贝对象时，不仅复制对象中的基本数据类型，还复制指针指向的内存区域。深拷贝确保每个对象都有自己的内存副本，互不干扰。

## 友元

### 友元函数

友元函数是一个可以访问类的私有和保护成员的普通函数。通过 friend 关键字声明。

```
class MyClass {
private:
    int x;
public:
    MyClass(int val) : x(val) {}
    friend void showX(const MyClass& obj);  // 声明友元函数
};

void showX(const MyClass& obj) {
    std::cout << "Value of x: " << obj.x << std::endl;  // 访问私有成员
}
```

### 友元类

友元类是可以访问另一个类的所有成员的类。通过 friend class 声明。

```
class MyClass {
private:
    int x;
public:
    MyClass(int val) : x(val) {}
    friend class FriendClass;  // 声明友元类
};

class FriendClass {
public:
    void showX(const MyClass& obj) {
        std::cout << "Value of x: " << obj.x << std::endl;  // 访问私有成员
    }
};
```

## 重写

重写是指在派生类中重新定义基类中已有的虚函数。重写后的函数会覆盖基类中的实现，并且通过基类指针或引用调用时，会执行派生类的实现。

```
class Base {
public:
    virtual void show() const {  // 基类中的虚函数
        std::cout << "Base show" << std::endl;
    }
};

class Derived : public Base {
public:
    void show() const override {  // 重写基类中的虚函数
        std::cout << "Derived show" << std::endl;
    }
};
```

### 重写的条件

1. 基类的函数必须是虚函数：重写发生在基类的虚函数和派生类的函数之间。如果基类的函数不是虚函数，那么即使派生类定义了一个同名函数，也不会发生重写，只会隐藏基类的函数。
2. 函数签名必须匹配：派生类中的函数必须与基类中的虚函数具有相同的函数签名（包括返回类型、参数类型和顺序），否则不会视为重写。

## 重载

重载是指在同一作用域中定义多个函数，这些函数具有相同的名字但参数列表不同（参数的类型、数量或顺序不同）。

```
class MyClass {
public:
    void show(int x) {
        std::cout << "Integer: " << x << std::endl;
    }
    void show(double x) {
        std::cout << "Double: " << x << std::endl;
    }
};
```

### override

override 是一个关键字，用于显式地指示派生类中的函数是用来重写基类中的虚函数的
有点：
避免拼写错误：如果你在派生类中重写一个虚函数时，不小心拼写了函数名错误，编译器会报告错误，因为 override 告诉编译器这个函数是用来重写基类的虚函数的。如果函数名不匹配，编译器会发出警告或错误。
确保基类中存在虚函数：使用 override 可以确保基类中存在一个具有相同函数签名的虚函数。如果基类中没有这样的虚函数，编译器会发出错误，帮助发现设计上的问题。

## 运算符重载

运算符重载是允许为用户定义的类型（如类）定义如何使用内置的运算符（如 +、- 等）。

```
// 后置递增运算符重载
MyClass operator++(int) {
	MyClass temp = *this;  // 保存当前值
	++value;  // 递增
	return temp;  // 返回递增前的值
}

// 前置递增运算符重载
MyClass& operator++() {
	++value;  // 先增加值
	return *this;  // 返回当前对象的引用
}
```

### 不可重载的运算符

::
->
.
?:
sizeof
typeid
static_cast、dynamic_cast、const_cast、reinterpret_cast - 类型转换运算符

## 类的实例化

类的实例化是指创建类的对象，这个过程会调用类的构造函数来初始化对象。

## 类对象模型

## 静态类

静态类通常是指只包含静态成员函数和静态成员变量的类，无法实例化对象。
静态类不能被实例化，因为所有成员都是静态的，定义对象实际上就是实例化里面的非静态成员，但是静态类并没有非静态成员，所以不用实例化。

静态类是密封(sealed)的。所谓是密封，就是不可被继承，不能拿来做父类。静态类不包括构造函数，因为构造函数就是在实例化对象是调用的，但是静态类又不能被实例化。静态类不能指定任何接口实现，不能有任何实例成员。

静态类的成员不能有protected或protected internal访问保护修饰符。静态类不能包含构造函数，但仍可声明静态构造函数以分配初始值或设置某个静态状态。

## 内部类

### 概念

如果一个类定义在另一个类的内部，这个内部类就叫做内部类。
注意此时这个内部类是一个独立的类，它不属于外部类，更不能通过外部类的对象去调用内部类。外部类对内部类没有任何优越的访问权限。
也就是说：内部类相当于外部类的友元类。注意友元类的定义，内部类中的方法可以通过外部类的对象参数来访问外部类中的所有成员(包括private)。但是外部类不是内部类的友元

```
#include <iostream>
using namespace std;
class A {
    private: 
        static int i;
        class B {}; // 这里B是private的，在A类外就不能使用A::B来定义内部类的对象。
};
int main(int argc, char* argv[])
{
   A::B *b = new A::B();
   return 0;
}
```

### 特性

• 内部类是外部类的友元类，但是外部类不是内部类的友元。（即内部类可以访问外部类）。
• 内部类定义在外部类的public、protected、private（）都是可以的；但是内部类受这些限制符的限定。
• 注意内部类可以直接访问外部类种的static成员，不需要外部类的对象/类名。

## 匿名类

在 C++ 中，匿名类是一种没有命名的局部类，它与匿名类似，但在 C++ 中有一些区别。匿名类是在声明的同时进行实例化的，它可以作为对象在堆栈上分配并使用，也可以作为类成员使用。

```
//可以使用lambda表达式来实现类似匿名类的功能
#include <iostream>

int main() {
    auto obj = []() {
        std::cout << "Hello, World!" << std::endl;
    };
    obj();
    return 0;
}
```

## 抽象类

抽象类是含有至少一个纯虚函数的类，不能被实例化，只能被派生类继承。

```
class AbstractClass {
public:
    virtual void pureVirtualFunction() = 0; // 纯虚函数
};
```

# 结构体

在c++里结构体与类的区别不大，唯一区别就是结构体的默认权限是public

## 结构体对齐

### 结构体对齐规则

1. 结构体的起始存储位置必须是能够被该结构体中最大的数据类型所整除。
2. 每个数据成员存储的起始位置是自身大小的整数倍(比如int在32位机为4字节，则int型成员要从4的整数倍地址开始存储)。
3. 结构体总大小（也就是sizeof的结果），必须是该结构体成员中最大的对齐模数的整数倍。若不满足，会根据需要自动填充空缺的字节。
4. 结构体包含另一个结构体成员，则被包含的结构体成员要从其原始结构体内部最大对齐模数的整数倍地址开始存储。(比如struct a里存有struct b，b里有char,int,double等元素,那b应该从8的整数倍开始存储。)
5. 结构体包含数组成员，比如char a[3],它的对齐方式和分别写3个char是一样的，也就是说它还是按一个字节对齐。如果写：typedef char Array[3],Array这种类型的对齐方式还是按一个字节对齐，而不是按它的长度3对齐。
6. 结构体包含共用体成员，则该共用体成员要从其原始共用体内部最大对齐模数的整数倍地址开始存储。

#### 默认对齐

对于结构体中的各个成员，第⼀个成员位于偏移为 0 的位置，以后的每个数据成员的偏移必须是min(#pragma pack() 制定的数，数据成员本身⻓度) 的倍数。
在所有的数据成员完成各⾃对⻬之后，结构体或联合体本身也要进⾏对⻬，整体⻓度是 min(#pragma pack()制定的数，⻓度最⻓的数据成员的⻓度) 的倍数。
64位操作系统上64位编译器：默认8字节对齐
64位操作系统上32位编译器：默认8字节对齐
32位操作系统上32位编译器：默认4字节对齐

### 查找方法

步骤一：前面单元的大小必须是后面单元大小的整数倍，如果不是就补齐

步骤二：整个结构体的大小必须是最大字节的整数倍

### 改变对齐方式的指令

#### #pragma pack(push, n) 和 #pragma pack(pop)

```
#pragma pack(push, 1)
struct ExamplePacked {
    char a;
    int b;
    short c;
};
#pragma pack(pop)
```

#### __attribute__((packed))

```
struct ExamplePacked {
    char a;
    int b;
    short c;
} __attribute__((packed));
```

# 接口

在C++中，接口通常使用抽象类来实现。抽象类是含有至少一个纯虚函数的类。纯虚函数是用 = 0 来标记的虚函数

# 继承

## 概念

继承(inheritance)机制是面向对象程序设计使代码可以复用的最重要的手段，它允许程序员在保持原有类特性的基础上进行扩展，增加功能，这样产生新的类，称派生类。

## 继承定义

## 继承关系和访问限定符

C++ 中的继承关系可以分为三种类型：
公共继承（public inheritance）: 子类继承了基类的所有公共成员和保护成员，访问权限保持不变。基类的公共成员在子类中仍然是公共的，保护成员在子类中仍然是保护的。
保护继承（protected inheritance）: 子类继承了基类的所有公共成员和保护成员，但它们在子类中变为保护成员。
私有继承（private inheritance）: 子类继承了基类的所有公共成员和保护成员，但它们在子类中变为私有成员。

## 继承的内存问题
### 非虚单继承
1）虚函数指针在最前面的位置。
2）成员变量根据其继承和声明顺序依次放在后面。
3）在单一的继承中，被overwrite的虚函数在虚函数表中得到了更新
### 虚函数单继承

### 非虚多继承
1） 每个父类都有自己的虚表指针。
2） 子类的成员函数被放到了第一个父类的虚表指针指向的地址中。
3） 内存布局中，其父类布局依次按声明顺序排列。
4） 每个父类的虚表中的f()函数都被overwrite成了子类的f()。这样做就是为了解决不同的父类类型的指针指向同一个子类实例，而能够调用到实际的函数。
### 虚函数多继承
## 菱形继承问题
### 二义性

在面向对象中，常常存在这样的事情，一个派生类它有两个或两个以上的基类，这种行为称作多重继承
如果在多重继承中Class A 和Class B存在同名数据成员，则对Class C而言这个同名的数据成员容易产生二义性问题。这里的二义性是指无法直接通过变量名进行读取，需要通过域(::)成员运算符进行区分

```
//基类A
class A 
{
public:
    A() :m_data(1), m_a(1)
    {
    }
    ~A(){}

public:
    int m_data;      //同名变量，类型无要求
    int m_a;
};
//基类B
class B
{
public:
    B() :m_data(1), m_b(1)
    {
    }
    ~B(){}

public:
    int m_data;      //同名变量，类型无要求
    int m_b;
};

class C  : public A, public B
{

};

int _tmain(int argc,  _TCHAR* argv[])
{
    C Data;
   //Data.m_data  = 10;   //错误, 提示指向不明确
   
   //通过域成员运算符才可以访问，使用不方便
    Data.A::m_data = 10.1; 
    Data.B::m_data = 20;
  
    std::cout << Data.A::m_data << "   " << Data.B::m_data << std::endl;

    return 0;
}

```

### 什么是菱形继承

在多重继承中，存在一个很特殊的继承方式，即菱形继承。比如一个类C通过继承类A和类B，但是类A和类B又同时继承于公共基类N
这种继承方式也存在数据的二义性，这里的二义性是由于他们间接都有相同的基类导致的。 这种菱形继承除了带来二义性之外，还会浪费内存空间。

```
//公共基类
class N
{
public:
    N(int data1, int data2, int data3) : 
        m_data1(data1), 
        m_data2(data2), 
        m_data3(data3)
    {
        std::cout << "call common constructor" << std::endl;
    }
    virtual ~N(){}

    void    display()
    {
        std::cout << m_data1 << std::endl;
    }

public :
    int     m_data1;
    int     m_data2;
    int     m_data3;
};


class A : /*virtual*/ public N
{
public:
    A() :N(11, 12, 13), m_a(1)
    {
        std::cout << "call class A constructor" << std::endl;
    }
    ~A(){}

public :
    int m_a;
};

class B :  /*virtual*/ public N
{
public:
    B() :N(21, 22, 23),m_b(2)
    {
        std::cout << "call class B constructor" << std::endl;
    }
    ~B(){}

public :
    int m_b;
};


class C : public A ,  public B
{
public:
    //负责对基类的初始化
    C() : A(), B(),
        m_c(3)
    {
        std::cout << "call class C constructor" << std::endl;
    }
    void show()
    {
        std::cout << "m_c=" << m_c << std::endl;
    }

 public :
    int m_c;
};

```

//
在类C中存在 两份的基类N，分别存在类A和类B中，如果数据多则严重浪费空间，也不利于维护,引用基类N中的数据还需要通过域运算符进行区分

### 菱形继承的解决

为了解决上述菱形继承带来的问题，C++中引入了虚基类，让子类只继承一次父类的父类，其作用是**在间接继承共同基类时只保留一份基类成员**

```
class A//A 基类
{ ... };

//类B是类A的公用派生类, 类A是类B的虚基类
class B : virtual public A
{  ... };

//类C是类A的公用派生类, 类A是类C的虚基类
class C : virtual public A
{  ... };

```

虚基类并不是在声明基类时声明的，而是在声明派生类时，指定继承方式声明的

#### 虚基类实现原理

虚拟继承使用继承虚基类来代替 继承基类的做法。注意是“代替”两个字。免不了让人惊讶，不过这也是虚拟继承的关键点。
继承虚基类又通过虚基表指针 与 其指向的虚基表来实现，这就是虚拟继承的三板斧。

##### 虚基表指针与虚基表

当使用虚拟继承时，原本的父类成员 会被替换为 一个虚基表指针，这个指针指向一张虚基表，虚基表里存放 虚基类与虚基表指针的偏移量。

# 多态

## 静态多态

静态多态（Static Polymorphism），也称为编译时多态（Compile-time Polymorphism），是在编译阶段决定的多态性。它主要通过函数重载和模板来实现。

1. 函数重载（Function Overloading）: 在同一个作用域中，可以定义多个同名函数，但参数列表（参数个数、类型或顺序）必须不同。编译器会根据传递给函数的参数类型和数量，选择合适的函数版本。

```
class Example {
public:
    void print(int i) {
        std::cout << "Integer: " << i << std::endl;
    }

    void print(double d) {
        std::cout << "Double: " << d << std::endl;
    }

    void print(std::string s) {
        std::cout << "String: " << s << std::endl;
    }
};
```

2. 模板（Templates）: 模板允许你编写通用的代码，能够根据不同的类型进行实例化，从而生成不同版本的函数或类。

```
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add(3, 4) << std::endl;        // 输出 7
    std::cout << add(3.5, 4.5) << std::endl;    // 输出 8.0
}
```

## 动态多态

### 概念

### 条件

多态有两个条件,任何一个不满足都不能执行多态 ,分别是

1. 虚函数的重写（重写）
2. 父类类型的指针或引用(接收父类对象或子类对象)的对象去调用虚函数

### 实现原理
动态多态是通过虚函数（virtual function）和虚函数表（vtable）实现的。当一个类包含虚函数时，编译器会为这个类生成一个虚函数表，其中存储了指向各个虚函数的指针。每个对象都有一个指向虚函数表的指针（vptr）。当通过基类指针或引用调用虚函数时，实际调用的是派生类中重写的函数版本。

# 异常
## 传统异常处理
传统的错误处理机制：
终止程序，如assert，缺陷：用户难以接受。如发生内存错误，除0错误时就会终止程序。
返回错误码，缺陷：需要程序员自己去查找对应的错误。如系统的很多库的接口函数都是通过把错误码放到 errno 中，表示错误
## C++的异常
### 概念
异常是一种处理错误的方式，当一个函数发现自己无法处理的错误时就可以抛出异常，让函数的 直接或间接的调用者处理这个错误。
throw: 当问题出现时，程序会抛出一个异常。这是通过使用 throw 关键字来完成的。
catch: 在您想要处理问题的地方，通过异常处理程序捕获异常.catch 关键字用于捕获异常，可以有多个catch进行捕获。
try: try 块中的代码标识将被激活的特定异常,它后面通常跟着一个或多个 catch 块。
如果有一个块抛出一个异常，捕获异常的方法会使用 try 和 catch 关键字。try 块中放置可能抛出异常的代码，try 块中的代码被称为保护代码。
```
try
 {
 // 保护的标识代码
}catch( ExceptionName e1 )
 {
 // catch 块
}catch( ExceptionName e2 )
 {
 // catch 块
}catch( ExceptionName eN )
 {
 // catch 块
}
```
### 异常的使用
#### 异常的抛出和捕获
##### 异常的抛出和匹配原则
##### 在函数调用链中异常栈展开匹配原则

# 类型转换
## 隐式转换
## 强制转换
c++提供了几种类型转换操作符，用于在不同类型之间进行转换。这些操作符包括：
1. static_cast：用于基本类型之间的转换，以及具有继承关系的类之间的向上转换（从派生类到基类）。
```
static_cast<type-id> (expression);
```
该运算符把 expression 转换为 type-id 类型，但没有运行时类型检查来保证转换的安全性
主要用法如下：
    （1）用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。
        进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；
        进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。
    （2）用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
    （3）把空指针转换成目标类型的空指针。
    （4）把任何类型的表达式转换成void类型。
需要注意的是，static_cast 不能转换掉 expression 的 const、volitale 或者 __unaligned 属性

1. const_cast：用于修改类型的const属性。可以将常量指针或引用转换为非常量指针或引用，反之亦然。
```
 const_cast<type-i> (expression)；
```
   
1. reinterpret_cast：用于进行低级别的类型转换，如将指针转换为整数或将一个类型的指针转换为另一个类型的指针。这种转换可能导致未定义行为，因此应谨慎使用。
reinterpret_cast 主要有三种强制转换用途：
  1、改变指针或引用的类型
  2、将指针或引用转换为一个足够长度的整形
  3、将整型转换为指针或引用类型。
```
reinterpret_cast <type-id> (expression)。
```
type-id 必须是一个指针、引用、算术类型、函数针或者成员指针。它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针

1. dynamic_cast：用于具有继承关系的类之间的向下转换（从基类到派生类）。dynamic_cast在运行时检查转换是否有效，如果转换无效，则返回空指针（对于指针类型）或抛出std::bad_cast异常（对于引用类型）。
```
dynamic_cast<type-id> (expression)。
```
几个特点如下：
  （1）其他三种都是编译时完成的，dynamic_cast 是运行时处理的，运行时要进行类型检查。
  （2）不能用于内置的基本数据类型的强制转换
  （3）dynamic_cast 要求 <> 内所描述的目标类型必须为指针或引用。dynamic_cast 转换如果成功的话返回的是指向类的指针或引用，转换失败的话则会返回 nullptr
  （4）在类的转换时，在类层次间进行上行转换（子类指针指向父类指针）时，dynamic_cast 和 static_cast 的效果是一样的。在进行下行转换（父类指针转化为子类指针）时，dynamic_cast 具有类型检查的功能，比 static_cast 更安全。 向下转换的成功与否还与将要转换的类型有关，即要转换的指针指向的对象的实际类型与转换以后的对象类型一定要相同，否则转换失败。在C++中，编译期的类型转换有可能会在运行时出现错误，特别是涉及到类对象的指针或引用操作时，更容易产生错误。Dynamic_cast操作符则可以在运行期对可能产生问题的类型转换进行测试。
  （5）使用 dynamic_cast 进行转换的，基类中一定要有虚函数，否则编译不通过（类中存在虚函数，就说明它有想要让基类指针或引用指向派生类对象的情况，此时转换才有意义）。这是由于运行时类型检查需要运行时类型信息，而这个信息存储在类的虚函数表中，只有定义了虚函数的类才有虚函数表

# c++内存管理
## 内存分布
代码段，数据段（常量区，全局和静态初始化区，全局和静态未初始化区（bss）），堆，栈
# c++ 11
## 右值引用与移动语义
前面写了
## lambad表达式
### 基本语法
```
[capture list] (parameter list) -> return type { function body }
```
capture list 是捕获列表，用于指定 Lambda表达式可以访问的外部变量，以及是按值还是按引用的方式访问。捕获列表可以为空，表示不访问任何外部变量，也可以使用默认捕获模式 & 或 = 来表示按引用或按值捕获所有外部变量，还可以混合使用具体的变量名和默认捕获模式来指定不同的捕获方式。 

parameter list 是参数列表，用于表示 Lambda表达式的参数，可以为空，表示没有参数，也可以和普通函数一样指定参数的类型和名称，还可以在 c++14 中使用 auto 关键字来实现泛型参数。

return type 是返回值类型，用于指定 Lambda表达式的返回值类型，可以省略，表示由编译器根据函数体推导，也可以使用 -> 符号显式指定，还可以在 c++14 中使用 auto 关键字来实现泛型返回值。

function body 是函数体，用于表示 Lambda表达式的具体逻辑，可以是一条语句，也可以是多条语句，还可以在 c++14 中使用 constexpr 来实现编译期计算。
## 包装器与绑定器
### 可调用对象
一般来说，可调用对象归类为以下6种：
普通的函数
函数指针
仿函数
类的静态成员函数
类的非静态成员函数
lambda表达式
### 使用包装器（function）
```
#include <iostream>
#include <functional>
#include <string>
using namespace std;

//1、普通的函数
void func(const string& str)
{
    cout << str << endl; 
}

//2、仿函数
class myclass1{
public:
    void operator()(const string& str)
    {   
        cout << str << endl; 
    }
};

//3、类中普通成员函数
class myclass2{
public:
    void func(const string& str)
    {
        cout << str << endl; 
    }
};

//4、类中静态成员函数
class myclass3{
public:
    static void func(const string& str)
    {
        cout << str << endl; 
    }
};

int main()
{
    //普通函数
    //由函数指针调用
    void(*fp1) (const string& ) = func;
    fp1("我是由函数指针调用的普通函数");
    //用包装器调用
    function<void(const string&)> ff1 = func;
    ff1("我是由包装器调用的普通函数");

    //仿函数
    myclass1 aa;
    aa("我是由仿函数对象调用的函数");
    // aa.operator()("我是由仿函数对象调用的函数");
    // myclass1{}.operator()("我是由仿函数对象调用的函数");
   //用包装器调用
    function<void(const string&)> ff2 = myclass1();
    ff2("我是由包装器调用的仿函数");

    //用函数指针调用的类的非静态成员函数
    myclass2 bb;
    void(myclass2::*fp3) (const string& ) = &myclass2::func; 
    (bb.*fp3)("我是由函数指针调用的类的非静态成员函数");
    //用包装器调用，传入类名
    function<void(myclass2, const string&)> ff3 = &myclass2::func;
    //需要传入this指针
    ff3(bb, "我是由包装器调用类的静态非成员函数");

    //用函数指针调用类的静态成员函数
    myclass3 cc;
    // cc.func("我是函数指针调用类的静态成员函数");
    void(*fp4)(const string& ) = myclass3::func; 
    fp4("我是函数指针调用类的静态成员函数");
    //用包装器调用
    function<void(const string&)> ff4 = myclass3::func;
    ff4("我是由包装器调用类的静态成员函数");

    //匿名函数
    auto f = [](const string& str)
    {
        cout << str << endl; 
    };
    f("我是lambda函数");
    //用包装器调用
    function<void(const string&)> ff5 = f;			
	ff5("我是由包装器调用的lambda函数");										

    return 0;
}
```
### 使用绑定器
```
//1、普通的函数
void func(int i, const string& str)
{
    while(i--)
    {
        cout << str << endl;
    }
    cout << endl;
}

//2、仿函数
class myclass1{
public:
    void operator()(int i, const string& str)
    {   
        while(i--)
        {
            cout << str << endl;
        }
        cout << endl;
    }
};

//3、类中普通成员函数
class myclass2{
public:
    void func(int i, const string& str)
    {
        while(i--)
        {
            cout << str << endl;
        }
        cout << endl;
    }
};

//4、类中静态成员函数
class myclass3{
public:
    static void func(int i, const string& str)
    {
        while(i--)
        {
            cout << str << endl;
        }
        cout << endl;
    }
};

int main()
{
    // 绑定普通函数 placeholders::_1是函数的第一个形参,placeholders::_2是第二个形参
    function<void(int, const string&)> fn1 = 
    bind(func, placeholders::_1, placeholders::_2);		
    fn1(2, "普通函数");
    
    // 类的静态成员函数
    function<void(int, const string&)> fn3 = 
    bind(myclass3::func, placeholders::_1, placeholders::_2);
    fn3(2, "类的静态成员函数");

    // 仿函数
    function<void(int, const string&)> fn4 = 
    bind(myclass1(), placeholders::_1, placeholders::_2);
    fn4(2, "仿函数");

    // 创建lambda对象
	auto lb = [](int i, const string& str) {
		while(i--)
        {
            cout << str << endl;
        }
        cout << endl;
	};
	function<void(int, const string&)> fn5 = 
	bind(lb, placeholders::_1, placeholders::_2);	
    fn5(2, "创建lambda对象");

    // 类的非静态成员函数，这样一来就可以通过模板的方式使用类的非静态成员函数的调用了
	myclass2 aa;
    function<void(int, const string&)> fn6 = 
    bind(&myclass2::func,&aa,placeholders::_1, placeholders::_2);
    fn6(2, "类的非静态成员函数");
    
    return 0;
}
```

# STL
## 算法

## 容器

## 迭代器

## 空间配置器
