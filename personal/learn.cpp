#include <atomic>
#include <thread>
#include <iostream>
using namespace std;

atomic_uint64_t i(1);

void Test1(){
    while(1){
        if(i.load()==1){
            cout << "1 ";
            i.store(2);
        }
    }
}

void Test2(){
    while(1){
        if(i.load()==2){
            cout << "2 ";
            i.store(3);
        }
    }
}

void Test3(){
    while(1){
        if(i.load()==3){
            cout << "3\n";
            i.store(1);
        }
    }
}

int main(){
    thread t3(Test3);
    thread t1(Test1);
    thread t2(Test2);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
