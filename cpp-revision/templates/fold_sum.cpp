#include <iostream>
#include <string>

using namespace std;

template <typename T, typename... Ts>
auto sumWithInit(Ts... args){
    T init = T{};
    T sum  = (init + ... + args);
    return sum;
}

int main(){
    cout <<sumWithInit<int>(4,3,9)<<endl;
    cout <<sumWithInit<string>("abc","def","kkf")<<endl;
    return 0;
}