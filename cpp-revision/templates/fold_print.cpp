#include <iostream>

using namespace std;

template <typename... Ts>
void print(Ts... args){
    //cout<<arg1<<arg2<<arg3
    (cout<<...<<args)<<endl;
}
template <typename... Ts>
void printWithComma(Ts... args){
    //cout<<arg1<<","<<arg2<<","<<arg3
    ((cout<<args<<(",")), ...);
}


int main(){
    print(1,2,"abc");
    printWithComma(3,5,"abc");
    return 0;
}