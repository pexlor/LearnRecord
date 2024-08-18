#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string> 
using namespace std;

int main(){
    string str;
    cin >> str;
    int i=0;
    for(;;){
        bool has = false;
        for(int j=0;j<str.size()-1;){
           if(str[j] == '0' && str[j+1] == '1'){
                cout << str << endl;
               str[j] = '1';
               str[j+1] = '0';
               cout << str << endl;
               j = j+2;
               //cout << j << endl;
               has = true;
           }else{
               ++j;
           }
        }
        if(!has){
            cout << i;
            break;
        }
        //cout << str << endl;
        ++i;
    }
    return 0;
}