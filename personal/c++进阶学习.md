# 原子操作
> c++原子操作性库官方文档 <https://cplusplus.com/reference/atomic/>

>原子性操作库(atomic)是C++11中新增的标准库，它提供了一种线程安全的方式来访问和修改共享变量，避免了数据竞争的问题。在多线程程序中，如果多个线程同时对同一个变量进行读写操作，就可能会导致数据不一致的问题。原子性操作库通过使用原子操作来保证多个线程同时访问同一个变量时的正确性。

>头文件： #include \<atomic>

## 原子变量
>原子性操作库(atomic)提供了多种类型的原子变量，包括bool 、char、short、int、long、long long等基本数据类型，以及intmax_t、uintmax_t、intptr_t等扩展类型。每个原子变量都有对应的原子类型，比如atomic_bool、atomic_char、atomic_int等。
1. 原子类型  
下面是原子性操作库中支持的一些原子类型：
| 原子类型 | 描述 |
| :--: | :--: |
| atomic_bool | 原子布尔型，只能存储true或false。 |
| atomic_char | 原子字符型，相当于char类型。 |
| atomic_uchar | 原子无符号字符型，相当于unsigned char类型。 |
| atomic_schar | 原子有符号字符型，相当于signed char类型。 |
| atomic_short | 原子短整型，相当于short类型。 |
| atomic_ushort | 原子无符号短整型，相当于unsigned short类型。 |
| atomic_int | 原子整型，相当于int类型。 |
| atomic_uint | 原子无符号整型，相当于unsigned int类型。 |
| atomic_long | 原子长整型，相当于long类型。 |
| atomic_ulong | 原子无符号长整型，相当于unsigned long类型。 |
| atomic_llong | 原子长长整型，相当于long long类型。 |
| atomic_ullong | 原子无符号长长整型，相当于unsigned long long类型。 |
| atomic_wchar_t | 原子宽字符型，相当于wchar_t类型。 |
| atomic_char16_t | 原子16位字符型，相当于char16_t类型。 |
| atomic_char32_t | 原子32位字符型，相当于char32_t类型。 |
| atomic_intmax_t | 原子最大宽度整数类型，对应<inttypes.h>中的intmax_t类型。 |
| atomic_uintmax_t | 原子最大宽度无符号整数类型，对应<inttypes.h>中的uintmax_t类型。 |
| atomic_intptr_t | 原子指针宽度整数类型，对应<stddef.h>中的intptr_t类型。 |
| atomic_uintptr_t | 原子指针宽度无符号整数类型，对应<stddef.h>中的uintptr_t类型。 |
| atomic_size_t | 原子size_t类型，用于表示对象的大小。 |
| atomic_ptrdiff_t | 原子ptrdiff_t类型，用于表示两个指针之间的距离。 |

**也可以使用atomic<type>模版创建**
## 原子类型函数

| 函数 | 描述 |
| :--: | :--: |
| load() | 原子读取操作，用于获取原子变量的当前值。 |
| store() | 原子写入操作，用于设置原子变量的值。 |
| exchange() | 原子交换操作，用于交换原子变量的值，并返回原始值。 |
| fetch_add() | 原子加法操作，用于增加原子变量的值，并返回原始值。 |
| fetch_sub() | 原子减法操作，用于减少原子变量的值，并返回原始值。 |
| fetch_and() | 原子按位与操作，用于按位与原子变量的值，并返回原始值。 |
| fetch_or() | 原子按位或操作，用于按位或原子变量的值，并返回原始值。 |
| fetch_xor() | 原子按位异或操作，用于按位异或原子变量的值，并返回原始值。 |
| exchange() | 阿斯顿 |
| compare_exchange_weak() | 阿斯顿 |
| compare_exchange_strong() | 阿斯顿 |
| test_and_set | asd |

**注意：以上函数只是原子类型库中的一部分函数，还有其他函数可用于更复杂的操作，具体取决于你的需求**

## 注意事项
### 原子操作不能拷贝
只要是原子操作，都不能进行赋值和拷贝（因为调用了两个对象，破坏了原子性--拷贝构造和拷贝赋值都会将第一个对象的值进行读取，然后再写入另外一个。对于两个独立的对象，这里就有两个独立的操作了，合并这两个操作必定是不原子的。因此，操作就不被允许。
### 做自旋锁
自旋锁是一种在多线程环境下保护共享资源的同步机制。它的基本思想是，当一个线程尝试获取锁时，如果锁已经被其他线程持有，那么该线程就会不断地循环检查锁的状态，直到成功获取到锁为止
```
std::atomic_flag spinLock = ATOMIC_FLAG_INIT; // 初始化自旋锁(自旋锁也用的锁)
 
void foo() {
    while (spinLock.test_and_set(std::memory_order_acquire)) {} // 尝试获取锁
    cout<<"thread "<<this_thread::get_id()<<" get spinlock!!!"<<endl;
    this_thread::sleep_for(chrono::seconds(10)); //先获取锁的线程延时，查看另一个线程CPU占用率
    spinLock.clear(std::memory_order_release); // 释放锁
}
 
int main() {
    std::thread t1(foo);
    std::thread t2(foo);
 
    t1.join();
    t2.join();
 
    return 0;
}

```

## 原子操作的内存顺序
| 内存模型 | 使用解读 | 内存序列选项 | 意义 |
| :--: | :--: | :--: | :--: |
| 排序一致性 | 如果不指定内存序列选项，默认都是该项 | ① memory_order_seq_cst | 提供了最强的内存排序保证。提供原子操作全局一致性，要求原子操作必须按照程序中出现的顺序执行，不会重新排序。优点：确保顺序执行；缺点：为全局顺序一致，每次写操作必须同步给其他核心，引入系统开销 |
| 获取-释放序列(非一致) | 用程序对性能有更高的要求，并且可以容忍一定程度的松散的内存排序。 | ② memory_order_consume（已取消） | 确保consume操作读取的值是最新，但不会像acquire-release构成关系，是一种弱同步内存序限制（只限制与consume有关原子操作）。由于实践中的问题和性能不佳，已在C++20中被取消。 |
|  |  | ③ memory_order_acquire | 用于读操作，其确保在读操作之前，所有先前的写操作（使用release）的结果都对当前线程可见。使得编译器对该部分操作不会重排序，而是按照顺序读取。 |
|  |  | ④ memory_order_release | 确保其余操作在执行release之前完成且对其他线程可见（使用release操作后其余线程读取之前会等待同步cache，确保数据同步）。注意：其他线程可见并不能保证其他线程读取成功！ |
|  |  | ⑤ memory_order_acq_rel | 确保前面的读取操作不会被后续的写入操作重排序，同时也确保后续的读取操作不会被前面的写入操作重排序，但不能强制像release一样保证写入操作的完成顺序。 |
| 自由序列(非一致) | 宽松的内存序列，它只保证操作的原子性，并不能保证多个变量之间的顺序性，也不能保证同一个变量在不同线程之间的可见顺序。 | ⑥ memory_order_relaxed | 只关心某个变量是否被修改，不关心修改发生的时间。优点：提高性能；缺点：不明确执行顺序。场景：多应用于无依赖原子操作、事件通知等。 | 

### memory_order_relaxed

### memory_order_seq_cst

### 
## 
# 泛型编程
