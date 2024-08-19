#include <atomic>
#include <iostream>
#include <memory>
template<class T>
class shared_ptr{
public:
    T* point;
    std::atomic_uint64_t * use_count;

    shared_ptr():point(nullptr),use_count(nullptr){

    }

    shared_ptr(T *point)
        :point(point)
        ,use_count(new std::atomic_uint64_t(1))
    {

    }

    shared_ptr(const shared_ptr<T> &sptr)
        :point(sptr.point)
        ,use_count(sptr.use_count)
    {
        ++(*use_count);
    }

    shared_ptr<T>& operator=(const shared_ptr<T> &sptr){
        if(this == &sptr){
            return this;
        }
        if(this->point&&--(*this->use_count)==0){
            delete this->point;
            delete this->use_count;
        }
        this->point = sptr.point;
        this->use_count = sptr.use_count;
        ++(*use_count);
        return *this;
    }

    ~shared_ptr(){
        --(*use_count);
        if(point&&(*use_count)==0){
            delete point;
            delete use_count;
        }
    }

    T* operator->(){
        return point;
    }

    T& operator*(){
        return *point;
    }
};

class A{
public:
    int a;
};

int main(){
    std::shared_ptr<int> p1(new int(1));
    shared_ptr<int> a(new int(1));
    shared_ptr<int> b(a);
    shared_ptr<int> c(b);
    shared_ptr<int> d = a;
    shared_ptr<A> aa(new A());
    std::cout << *(a.use_count) << std::endl;
    std::cout << *(b.use_count) << std::endl;
    std::cout << *(c.use_count) << std::endl;
}