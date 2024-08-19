#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string> 
using namespace std;

class a{
public:
    int a;
    virtual void Test();
};

class f : public a{
    bool f;
    bool c;
    bool d;
    bool g;
    bool h;
};

class b : virtual public a{
 
};

class c : virtual public a{

};

class d : public b, public c{

};

int main(){
    cout << sizeof(a) << endl;
    cout << sizeof(b) << endl;
    cout << sizeof(c) << endl;
    cout << sizeof(d) << endl;
    cout << sizeof(f) << endl;
    return 0;
}