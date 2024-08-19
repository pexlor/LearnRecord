#include <iostream>
#include <memory>
template<class T>
class unique_ptr{
public:
    T * point;
    unique_ptr():point(nullptr){

    }

    unique_ptr(T * point):point(point){
        
    }

    unique_ptr(const unique_ptr<T> && ptr):point(ptr.point){
        ptr.point = nullptr;
    }

    unique_ptr(const unique_ptr<T> &) = delete;

    unique_ptr<T>& operator=() = delete;

    T* operator->(){
        return point;
    }

    T& operator*(){
        return *point;
    }

    ~unique_ptr(){
        delete ptr;
    }
};

class A{
public:
    int a;
};

int main(){
    unique_ptr<A> up(new A());
    unique_ptr<A> dp(std::move(up));
    std::unique_ptr<A> ap(new A());
    
}