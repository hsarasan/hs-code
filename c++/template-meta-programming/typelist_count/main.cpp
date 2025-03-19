#include <iostream>

using namespace std;

template <typename... Args>
struct TypeCount{
    constexpr static int value=sizeof...(Args);

};


int main(){
    cout<<TypeCount<int,char,short>::value<<endl; 
    return 0;
} 