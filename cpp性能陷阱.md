# 要了解的c++十个性能陷阱

## （一）虚函数

    老生常谈的性能损耗，这里只介绍一下虚函数调用带来的成本：

    1. 会多一次寻址操作，去虚函数表查询函数的地址。

    2. 可能会破坏cpu流水线，因为虚函数调用是一次间接调用，需要进行分支预测。

    3. 阻碍了编译器内联，大部分情况下，虚函数是无法被内联的（与前两条相比，无法内联才是虚函数性能损耗的主要来源）。

    然而在实际生产环境中，可能很多的运行时多态是无法避免的，毕竟这是OOP的基础特性，因此对于虚函数我们也只能了解背后的成本而已。某些情况下我们可以使用编译期多态来替代虚函数，比如CRTP(Curiously Recurring Template Pattern)、Tempated Visitor Pattern、Policy Based Design等等。

## （二）隐形的拷贝

    也是一个老生常谈的性能损耗，这里主要介绍几个容易被疏忽的场景：

    Member Initialization构造函数
    
``` 
class C {  
public:  
    C(A a, B b): a_(a), b_(b){}  
private:  
    A a_;  
    B b_;  
}  

int main() {
    A a;  
    B b;  
    C c(a, b);  
} 
```

  如果A、B是非平凡的类，会各被复制两次，在传入构造函数时一次，在构造时一次。C的构造函数应当改为：

  C(A a, B b): a_(std::move(a)), b_(std::move(b)){}
这种写法是clang-tidy推荐的clang.llvm.org/extra... ，相比传const引用进来，如果外面也是传右值，则完全没有拷贝。

For循环

std::vector<std::string> vec;
for(std::string s: vec){
  // ...
}
这里每个string会被复制一次，改为for(const std::string& s: vec)即可.

Lambda捕获

A a;
auto f = [a]{};
lambda函数在值捕获时会将被捕获的对象拷贝一次，可以根据需求考虑使用引用捕获auto f = [&a]{};或者用std::move捕获初始化auto f = [a = std::move(a)]{};（仅限C++14以后）。

隐式类型转换

std::unordered_map<int, std::string> map;
for(const std::pair<int, std::string>& p: map){
  // ...
}
这是一个很容易被忽视的坑点，这段代码用了const引用，但是因为类型错了，所以还是会发生拷贝，因为unordered_map element的类型是std::pair<const int, std::string>，所以在遍历时，推荐使用const auto&，对于map类型，也可以使用结构化绑定（参考我的另一篇文章《C++17在业务代码中最好用的十个特性 》）。

（三）隐形的析构

在C++代码中，我们几乎不会主动去调用类的析构函数，都是靠实例离开作用域后自动析构。而“隐形”的析构调用，也会导致我们的程序运行变慢：

复杂类型的析构

我们的业务代码中有这样一种接口

int Process(const Req& req, Resp* resp) {
  Context ctx = BuildContext(req); // 非常复杂的类型
  int ret = Compute(ctx, req, resp); // 主要的业务逻辑
  PrintTime();
  return ret; 
}

int Api(const Req& req, Resp* resp) {
  int ret = Process(req, resp);
  PrintTime();
}
在日志中，Process函数内打印的时间和PrintTime打印的时间竟然差了20毫秒，而我们当时接口的总耗时也不过几十毫秒，我当时百思不得其解，还是靠我老板tomtang一语道破先机，原来是析构Context足足花了20ms。后面我们实现了Context的池化，直接将接口耗时降了20%。

平凡析构类型

如何定义类的析构函数也大有讲究，看下下面这段代码：

class A {
 public:
  int i;
  int j;
  ~A() {};
};

A get() {
  return A{41, 42};
}
get函数对应的汇编代码是：

get():                                # @get()
        movq    %rdi, %rax
        movabsq $180388626473, %rcx             # imm = 0x2A00000029
        movq    %rcx, (%rdi)
        retq
而如果我能把析构函数改一下：

class A {
 public:
  int i;
  int j;
  ~A() = default; // 注意这里
};

A get() {
  return A{41, 42};
}
对应的汇编代码则变成了：

get():                                # @get()
        movabsq $180388626473, %rax             # imm = 0x2A00000029
        retq
前者多了两次赋值，也多用了两个寄存器，原因是前者给类定义了一个自定义的析构函数（虽然啥也不干），会导致类为不可平凡析构类型(std::is_trivially_destructible)和不可平凡复制类型（std::is_trivially_copyable），根据C++的函数调用ABI规范，不能被直接放在返回的寄存器中（%rax），只能间接赋值。除此之外，不可平凡复制类型也不能作为编译器常量进行编译器运算。所以，如果你的类是平凡的（只有数值和数字，不涉及堆内存分配），千万不要随手加上析构函数！

关于非平凡析构类型造成的性能损耗，后文还会多次提到。

（四）滥用std::shared_ptr

C++核心指南是这样推荐智能指针的用法的：

用 std::unique_ptr或 std::shared_ptr表达资源的所有权。

不涉及所有权时，用裸指针。

尽量使用std::unique_ptr，只有当资源需要被共享所有权时，再用std::shared_ptr。

但是在实际代码中，用std::shared_ptr的场景大概就是以下几种：

小部分是因为代码作者是写python或者java来的，不会写没有gc的代码（比如apache arrow项目，所有数据全用std::shared_ptr，像是被apache的Java环境给荼毒了）。

绝大部分是因为代码作者是会写C++的，但是太懒了，不想梳理内存资源模型。不得不说，std::shared_ptr确实是懒人的福音，既保证了资源的安全，又不用梳理资源的所有权模型。

很小一部分是因为确实需要使用std::shared_ptr的场景（不到10%）。我能想到的必须用std::shared_ptr的场景有：异步析构，缓存。除此之外想不出任何必须的场景，欢迎小伙伴们在评论区补充。

实际上，std::shared_ptr的构造、复制和析构都是非常重的操作，因为涉及到原子操作，std::shared_ptr是要比裸指针和std::unique_ptr慢10%～20%的。即使用了std::shared_ptr也要使用std::move和引用等等，尽量避免拷贝。

std::shared_ptr还有个陷阱是一定要使用std::make_shared<T>()而不是std::shared_ptr<T>(new T)来构造，因为后者会分配两次内存，且原子计数和数据本身的内存是不挨着的，不利于cpu缓存。

（五）类型擦除：std::function和std::any

std::function，顾名思义，可以封装任何可被调用的对象，包括常规函数、类的成员函数、有operator()定义的类、lambda函数等等，当我们需要存储函数时std::function非常好用，但是std::function是有成本的：

std::function要占用32个字节，而函数指针只需要8个字节

std::function本质上是一个虚函数调用，因此虚函数的问题std::function都有，比如无法内联

std::function可能涉及堆内存分配，比如lambda捕获了大量值时，用std::function封装会需要在堆上分配内存

因此我们只应在必须时才使用std::function，比如需要存储一个不确定类型的函数。而在只需要多态调用的，完全可以用模版静态派发：

template <typename Func>
void Run(Func&& f){
  f();
}
std::any同理，用类型擦除的机制可以存储任何类型，但是也不推荐使用。

（六）std::variant和std::optional

我在我的另一篇文章《C++17在业务代码中最好用的十个特性 》大肆吹捧了一波std::variant和std::optional，但是说实话，C++的实现还是有些性能开销的，这里以std::optional为例介绍：

必须的多余内存开销：简单来说，std::optional<T>有两个成员变量，类型分别为bool和T，由于内存对齐的原因，sizeof(std::optional<T>)会是sizeof(T)+alignof(T)，对于简单的类型，sizeof(std::optional<T>)甚至会是sizeof(T)的两倍。相比之下，rust语言的option实现则有null pointer optimization，即如果一个类的合法内存表示一定不会全部字节为零，比如std::reference_wrapper，那就可以零开销地表示std::optional<T>，而C++由于需要兼容C的内存对齐，不可能实现这项优化

c++标准要求如果T是可平凡析构的（见上文析构的部分），std::optional<T>也必须是平凡析构的，但是gcc在8.0.0之前的实现是有bug的，所有std::optional<T>都被设置为了非平凡类型，所以用std::optional作为工厂函数的返回值是由额外性能开销的。

对NRVO（返回值优化）不友好，见下文NRVO的部分。

（七）std::async

std::async是一个很好用的异步执行抽象，但是在使用的时候可能一不小心，你的代码就变成了同步调用：

不指定policy

std::async的接口是：

template< class Function, class... Args >
std::future<std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>>
    async( Function&& f, Args&&... args );

template< class Function, class... Args >
std::future<std::invoke_result_t<std::decay_t<Function>, std::decay_t<Args>...>>
    async( std::launch policy, Function&& f, Args&&... args );
其中std::launch类型包括两种：std::launch::async异步执行和std::launch::deferred懒惰执行，如果你使用第一种接口不指定policy，那么编译器可能会自己帮你选择懒惰执行，也就是在调用future.get()的时候才同步执行。

不保存返回值

这是c++的std::async的一个大坑点，非常容易踩坑，比如这段代码：

void func1() { 
  // ... 
}

void func2() { 
  // ... 
}

int main() {
  std::async(std::launch::async, func1);
  std::async(std::launch::async, func2);
}
在这段代码里，func1和func2其实是串行的！因为std::async会返回一个std::future，而这个std::future在析构时，会同步等待函数返回结果才析构结束。这也是上文“隐形的析构”的另外一种表现。正确的代码应当长这样：

auto future1 = std::async(std::launch::async, func1);
auto future2 = std::async(std::launch::async, func2);
更奇葩的是，只有std::async返回的std::future在析构时会同步等待，std::packaged_task，std::promise构造的std::future都不会同步等待，实在是让人无力吐槽。

关于std::async等等C++多线程工具，在我之后的文章《现代C++并发编程指南》会介绍，敬请期待。

与编译器作对

众所周知，现代编译器是非常强大的。毛主席曾经说过：要团结一切可以团结的力量。面对如此强大的编译器，我们应该争取做编译器的朋友，而不是与编译器为敌。做编译器的朋友，就是要充分利用编译器的优化。而很多优化是有条件的，因此我们要争取写出优化友好的代码，把剩下的工作交给编译器，而不是自己胡搞蛮搞。

（八）返回值优化NRVO（Named Return Value Optimization)

当一个函数的返回值是当前函数内的一个局部变量，且该局部变量的类型和返回值一致时，编译器会将该变量直接在函数的返回值接收处构造，不会发生拷贝和移动，比如：

#include <iostream>

struct Noisy {
  Noisy() { std::cout << "constructed at " << this << '\n'; }
  Noisy(const Noisy&) { std::cout << "copy-constructed\n"; }
  Noisy(Noisy&&) { std::cout << "move-constructed\n"; }
  ~Noisy() { std::cout << "destructed at " << this << '\n'; }
};

Noisy f() {
  Noisy v = Noisy();
  return v;
}
void g(Noisy arg) { std::cout << "&arg = " << &arg << '\n'; }

int main() {
  Noisy v = f();
  g(f());
}
这段代码中，函数f()满足NRVO的条件，所以Noisy既不会拷贝，也不会move，只会被构造和析构两次，程序的输出：

constructed at 0x7fff880300ae
constructed at 0x7fff880300af
&arg = 0x7fff880300af
destructed at 0x7fff880300af
destructed at 0x7fff880300ae
滥用std::move

自从C++11加入std::move语义之后，有些“自以为是”的程序员会到处添加move。在这些情况下，std::move是根本没用的：

被move的对象是平凡类型。

被move的对象是一个常量引用。

而在某些情况下，move反而会导致负优化，比如阻碍了NRVO：

Noisy f() {
  Noisy v = Noisy();
  return std::move(v);
}
还是上面的代码，只不过返回值被改成move走，结果就多了两次move构造和两次析构，反而得不偿失：

constructed at 0x7ffc54006cdf
move-constructed
destructed at 0x7ffc54006cdf
constructed at 0x7ffc54006cdf
move-constructed
destructed at 0x7ffc54006cdf
&arg = 0x7ffc54006d0f
destructed at 0x7ffc54006d0f
destructed at 0x7ffc54006d0e
工厂返回std::optional

同样的，使用std::optional也可能会阻碍NRVO优化：

std::optional<Noisy> f() {
  Noisy v = Noisy();
  return v;
}
因为返回值类型不对应，因此应当改为

std::optional<Noisy> f() {
  std::optional<Noisy> v;
  v = Noisy();
  return v;
}
为了性能牺牲了部分可读性。

（九）尾递归优化

尾递归优化是函数式语言常用的一种优化，如果某个函数的最后一步操作是调用自身，那么编译器完全可以不用调用的指令(call)，而是用跳转(jmp)回当前函数的开头，省略了新开调用栈的开销。然而由于C++的各种隐形操作，尾递归优化不是那么好实现。我曾经在知乎上看到这样一个问题：https://www.zhihu.com/question/552352098。题主的函数长这样：

unsigned btd_tail(std::string input, int v) {
    if (input.empty()) {
        return v;
    } else {
        v = v * 2 + (input.front() - '0');
        return btd_tail(input.substr(1), v);
    }
}
直接return自身的调用，如果在函数式语言就是一个标准的尾递归，然而，实际执行的代码是：

unsigned btd_tail(std::string input, int v) {
    if (input.empty()) {
        return v;
    } else {
        v = v * 2 + (input.front() - '0');
        auto temp = btd_tail(input.substr(1), v);
        input.~string(); // 注意这里
        return temp;
    }
}
由于在return前C++有隐形的析构操作，所以这段代码并不是尾递归。而需要析构的本质原因是std::string不是可平凡析构的对象，解决办法也很简单，换成std::string_view就好了

unsigned btd_tail(std::string_view input, int v) {
    if (input.empty()) {
        return v;
    } else {
        v = v * 2 + (input.front() - '0');
        return btd_tail(input.substr(1), v);
    }
}
std::string_view是可平凡析构的，所以编译器根本不需要调用析构函数，这也是上文推荐尽量选用可平凡析构对象的另一个理由。关于std::string_view的介绍，可参考我的另一篇文章《C++17在业务代码中最好用的十个特性 》。我的下一篇文章《C++函数式编程指南》会介绍C++函数式编程，敬请期待。

（十）自动向量化优化

现代CPU大部分都支持一些向量化指令集如SSE、AVX等，向量化指的是SIMD操作，即一个指令，多条数据。在某些条件下，编译器会自动将循环优化为向量化操作：

循环内部访问的是连续内存

循环内部没有函数调用，没有if分支

循环之间没有依赖

举个例子，下方的代码非常的向量化不友好：

enum Type { kAdd, kMul };
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

std::vector<int> func(std::vector<int> a, std::vector<int> b, Type t) {
  std::vector<int> c(a.size());
  for (int i = 0; i < a.size(); ++i) {
    if (t == kAdd) {
      c[i] = add(a[i], b[i]);
    } else {
      c[i] = mul(a[i], b[i]);
    }
  }
  return c;
}
既有if，又有函数调用，而如果我们通过模版if和内联函数，这两条都可以规避：

enum Type { kAdd, kMul };
inline __attribute__((always_inline)) int add(int a, int b) { return a + b; }
inline __attribute__((always_inline)) int mul(int a, int b) { return a * b; }

template <Type t>
std::vector<int> func(std::vector<int> a, std::vector<int> b) {
  std::vector<int> c(a.size());
  for (int i = 0; i < a.size(); ++i) {
    if constexpr (t == kAdd) {
      c[i] = add(a[i], b[i]);
    } else {
      c[i] = mul(a[i], b[i]);
    }
  }
  return c;
}
这样就变成了向量化友好的代码。关于if constexpr的介绍可以参考我的另一篇文章《C++17在业务代码中最好用的十个特性 》。另外我们团队正在基于apache arrow做一些向量化计算的工作，后续也会有文章分享关于向量化优化的详细介绍。