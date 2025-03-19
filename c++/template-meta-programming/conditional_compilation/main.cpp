#include <iostream>
#include <type_traits>

using namespace std;

template <typename T>
typename std::enable_if_t<is_integral_v<T>,void>
print(T t){
    cout<<"IMplestemend t= "<<t<<endl;
}

int main(){
    //print(2.5);
    print(2);
    return 0;
}