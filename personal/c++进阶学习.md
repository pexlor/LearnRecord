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
# 泛型编程
