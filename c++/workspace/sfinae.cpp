#include <iostream>

using namespace std;

template <typename T>
enable_if_t< is_integral_v<T>,void>
f(){
    cout<<"Is an integral type "<<endl;
}

int main(){
    
    return 0;
}
