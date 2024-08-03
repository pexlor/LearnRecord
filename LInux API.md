> Linux 系统编程学习  

> Linux系统编程博大精深，学习时间很长，本篇学习顺序不限，仅个人总结与复习使用

> 参考书籍：Linux/Unix 系统编程手册

> 再补充一句，文中的代码来自Linux-4.0-rc1,Linux6.0以上版本代码有较大差异

# 进程与线程
## 进程创建与控制
### 进程前置知识  

    1. 进程的概念
    进程的定义：一个执行中程序的实例，即一个正在执行的程序。
    如果站在内核的角度来看：进程是分配系统资源的单位。

    2. 进程控制块（PCB）
    进程是一个抽象的概念，那么就需要一个具体的数据结构来描述。进程中的信息就被放在了一个叫做进程控制块(PCB)的结构体中。在Linux中PCB是一个结构体（名称为 task_struct），这里PCB的代码太长了，就不展示了，大致包含以下内容：
>标识符（PID）：与进程相关的唯一标识符，用来区别其他进程  
>状态：进程会有不同的状态，如运行，停止等等  
>优先级：相对于其他进程的优先顺序  
>程序计数器：程序中即将执行的下一条指令的地址  
>内存指针：包括程序代码和进程相关数据的  
>上下文信息：进程执行时CPU的寄存器中的数据  
>IO状态信息： 包括显示的I/O请求，分配给进程的I/O设备和正在被进程使用的文件列表。  
>记账信息：可能包括处理器时间总和，使用的时钟总数，时间限制，记账号等  `

    3. 进程状态
    运行态：
    并不意味着进程一定在运行中，它表明进程要么是在运行中要么在运行队列  

    就绪态：

    睡眠态(阻塞态)：
    休眠状态是在等待某种条件就绪，在休眠状态，可被操作系统杀死，也叫浅度睡眠。
    处于这个状态的进程因为等待某某事件的发生（比如等待socket连接、等待信号量），而被挂起。这些进程的task_struct结构被放入对应事件的等待队列中。当这些事件发生时（由外部中断触发、或由其他进程触发），对应的等待队列中的一个或多个进程将被唤醒。

    磁盘休眠态：
    有时候也叫不可中断睡眠状态（uninterruptible sleep），在这个状态的进程通常会等待IO的结束。

    停止态：
    可以通过发送 SIGSTOP 信号给进程来停止（T）进程。这个被暂停的进程可以通过发送 SIGCONT 信号让进程继续运行

    死亡态：
    进程死亡

    僵尸态：
    表示进程已经结束了，但是其父进程还没有调用wait4或waitpid()来释放进程描述符。为了父进程能够获知它的消息，子进程的进程描述符仍然被保留着。一旦父进程调用了wait4()，进程描述符就会被释放。

    孤儿进程：
    当一个进程的父进程结束时，但是它自己还没有结束，那么这个进程将会成为孤儿进程。
    孤儿进程会被init进程（1号进程）的进程收养，当然在子进程结束时也会由init进程完成对它的状态收集工作，因此一般来说，孤儿进程并不会有什么危害.

    4. 进程优先级
    优先级觉得进程拿到资源的顺序

    5. 进程地址空间
    在Linux中进程地址空间称之为struct mm_struct(内存描述符)的结构体。Linux就是通过这个结构体来实现「内存管理」的。mm_struct结构是对整个用户空间的描述（每个内存分段的起始）

    vm_area_struct 描述了这些虚拟内存区域 VMA

### 进程创建
1. fork()  
```
#include <unistd.h>  
pid_t fork(void);  
```
特性：子进程会复制父进程的PCB，二者之间代码共享，数据独有，拥有各自的进程虚拟地址空间。

写时拷贝技术：子进程创建出来后，与父进程映射访问同一块物理内存，但当父子进程当中有任意一个进程更改了内存中的数据时，会给子进程重新在物理内存中开辟一块空间，并将数据拷贝过去。 这样避免了直接给子进程重新开辟内存空间，造成内存数据冗余。换句话说，如果父子进程都不更改内存中的值，那他们二者各自的进程虚拟地址空间通过页表映射，始终是指向同一块物理内存。

2. vfork()
vfork()和fork()一样都是创建一个子进程，但二者是有区别的

由vfok创建出来的子进程共享了父进程的所有内存，包括栈地址，直至子进程使用execve启动新的应用程序为止
由vfork创建出来得子进程不应该使用return返回调用者，应该使用exit()或者_exit()函数来退出
由vfork创造出来的子进程还会导致父进程挂起，除非子进程exit或者execve才会唤起父进程,要等子进程结束才能运行父进程

3. clone()
>创建轻量级进程（也就是线程），pthread库基于此实现

```
int clone(int (*fn)(void *), void *child_stack, int flags, void *arg);  
```
fn为函数指针，此指针指向一个函数体，即想要创建进程的静态程序（我们知道进程的4要素，这个就是指向程序的指针，就是所谓的“剧本", ）；

child_stack为给子进程分配系统堆栈的指针（在linux下系统堆栈空间是2页面，就是8K的内存，其中在这块内存中，低地址上放入了值，这个值就是进程控制块task_struct的值）；

arg就是传给子进程的参数一般为（0）；

flags为要复制资源的标志，描述你需要从父进程继承那些资源（是资源复制还是共享)

### 进程终止
exit（ ）终止函数
### 进程等待
wait() 函数
### 进程替换
exec()系列

## 进程间通信
1. 匿名管道
> 管道是一种单向的数据通道，即数据通道中的数据一次只能向一个方向移动。这是一种半双工方法，为了实现全双工，需要另一根管道，形成一组双通道

> 匿名管道最基本的管道类型，它是一个临时的、单向的数据通道，通常用于具有亲缘关系的进程（如父子进程）之间的通信。匿名管道没有名称，它们在管道创建时只在进程内有效，无法在系统中被其他进程访问

```
int pipefd[2];
if (pipe(pipefd) == -1) {     
    perror("pipe");     
    exit(EXIT_FAILURE); 
}
// pipefd[0]用于读取数据，而pipefd[1]用于写入数据
write(pipefd[1], message, strlen(message));

size_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));
```
2. 有名管道
> 命名管道是一种具有名称的特殊文件，它在文件系统中存在，允许不相关的进程之间进行通信。
```
const char *fifo = "/tmp/myfifo";
// 创建命名管道
if (mkfifo(fifo, 0666) == -1) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
}
```
3. 消息队列
>消息队列 (Message Queue) 允许进程在两个进程之间以消息的形式交换数据。它允许进程通过相互发送消息来异步通信，其中消息存储在队列中，等待处理，并在处理后删除

>消息队列是在非共享内存环境中使用的缓冲区，其中任务通过相互传递消息而不是通过访问共享变量进行通信。任务共享一个公共缓冲池。消息队列是一个无界 FIFO 队列，可防止不同线程的并发访问

```
/// 创建或者打开消息队列API
int msgget(key_t key, int msgflg);

///向队列中添加消息的API
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

///读取消息队列中的消息，（成功返回消息的长度，失败返回 -1）
msgrcv(int msqid, void *msg_ptr, size_t msg_sz, long int msgtype, int msgflg);

///控制消息队列，成功返回0，失败返回 -1
int msgctl(int msqid, int cmd, struct msqid_ds *buf);

```

4. 共享内存
>共享内存是两个或多个进程之间共享的内存,允许多个进程访问和共享相同内存块。每个进程都有自己的地址空间；如果任何进程想要将某些信息从其自己的地址空间与其他进程进行通信，则只能使用 IPC（进程间通信）共享内存技术。
>共享内存是最快的进程间通信机制。操作系统将多个进程的地址空间中的内存段映射到该内存段中读取和写入，而无需调用操作系统函数
```
#include <sys/ipc.h>   
#include <sys/shm.h>   

int shmget (key_t key, size_t size, int shmflg);  //用于创建共享内存段

void *shmat(int shmid, const void *shmaddr, int shmflg);  //用于将共享段与进程的地址空间附加
```

写进程：
```
#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<sys/shm.h>  
#include<string.h>  
int main()  
{  
	int i;  
	void *shared_memory;  
	char buff[100];  
	int shmid;  
	shmid=shmget((key_t)2345, 1024, 0666|IPC_CREAT);   
	//creates shared memory segment with key 2345, having size 1024 bytes. 
	printf("Key of shared memory is %d\n",shmid);  
	shared_memory=shmat(shmid,NULL,0);   
	//process attached to shared memory segment  
	printf("Process attached at %p\n",shared_memory);   
	//this prints the address where the segment is attached with this process  
	printf("Enter some data to write to shared memory\n");  
	read(0,buff,100); //get some input from user  
	strcpy(shared_memory,buff); //data written to shared memory  
	printf("You wrote : %s\n",(char *)shared_memory);  
}  
```
读进程：
```
#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<sys/shm.h>  
#include<string.h>  
int main()  
{  
	int i;  
	void *shared_memory;  
	char buff[100];  
	int shmid;  
	shmid=shmget((key_t)2345, 1024, 0666);  
	printf("Key of shared memory is %d\n",shmid);  
	shared_memory=shmat(shmid,NULL,0); //process attached to shared memory segment  
	printf("Process attached at %p\n",shared_memory);  
	printf("Data read from shared memory is : %s\n",(char *)shared_memory);  
}  
```
5. 信号
信号（Signals）是一种重要的机制，用于通知进程发生了某种事件或异常。
信号是一种异步通知机制，用于在软件层面向进程发送通知
每种信号都由一个唯一的整数编号表示

```
kill(pid, sig) ///向指定的进程 pid 发送信号 sig


signal(sig, handler) ///进程可以通过注册信号处理函数来捕获和处理信号
sigaction(sig, &act, &oldact)

void handler(int sig) ///信号处理函数是一个特殊的函数，用来处理特定信号发生时的行为。这些函数必须满足特定的格式
```

```
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SIG_CUSTOM SIGUSR1  // 自定义信号

void error_handling(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    pid_t pid = fork();  // 创建子进程
    if (pid < 0) {
        error_handling("Fork error");
    } else if (pid == 0) {
        // 子进程（接收进程）
        execl("./receiver", "receiver", NULL);  // 执行接收进程程序
        error_handling("Exec error");
    } else {
        // 父进程（发送进程）
        sleep(1);  // 等待子进程初始化完毕

        printf("Sending signal to child process (PID: %d)...\
", pid);
        if (kill(pid, SIG_CUSTOM) == -1) {
            error_handling("Kill error");
        }

        printf("Signal sent.\
");
    }

    return 0;
}
```

```
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SIG_CUSTOM SIGUSR1  // 自定义信号

void sig_handler(int sig) {
    if (sig == SIG_CUSTOM) {
        printf("Received custom signal SIGUSR1.\
");
    }
}

int main() {
    struct sigaction act;
    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    // 设置自定义信号的处理函数
    if (sigaction(SIG_CUSTOM, &act, NULL) == -1) {
        perror("Sigaction error");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for signal...\
");

    while (1) {
        sleep(1);  // 让程序持续运行
    }

    return 0;
}

```

4. socket
> 详细见网络编程
```
socket()//创建套接字，返回一个文件描述符。
bind()// 将套接字绑定到一个地址，如 IP 地址和端口号。
listen()// 仅用于流套接字，将套接字标记为被动套接字，等待连接请求。
accept()// 仅用于流套接字，接受客户端的连接请求，返回一个新的文件描述符用于与客户端通信。
connect()// 仅用于流套接字，连接到远程套接字（客户端）。
send();recv()// 发送和接收数据。
sendto();recvfrom()// 用于数据报套接字，发送和接收数据报。
```

## 同步与互斥
### 线程同步与互斥
1. 互斥锁
2. 自旋锁
3. 信号量
4. 条件变量
5. 读写锁
6. 屏障

### 进程同步方式
1. 信号量
2. 文件锁
3. 互斥量
4. 无锁CAS
5. 校验方式


# 文件IO

# 网络编程

# 定时器

# 内存管理
