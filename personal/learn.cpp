#include <atomic>
using namespace std;

int main(){
    atomic_bool a;
    atomic<bool> b;
    a.load();
}
