#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
void print(T t){
    if constexpr (is_integral_v<T>){
        cout<<"IMplemented "<<endl;
    }
    else{
        cout<<"What?"<<endl;
    }
}

int main(){
    print(2.5);
    print(2);
    return 0;
}