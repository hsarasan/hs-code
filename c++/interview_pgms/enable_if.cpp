#include <iostream>

using namespace std;

template <typename T>
typename std::enable_if_t<is_integral_v<T>,void>
f(){
    cout<<"Integral type "<<endl;
}

int main(){
    f<int>();
    f<void>();
    return 0;
}