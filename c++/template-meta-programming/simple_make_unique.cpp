#include <iostream>
#include <memory>

using namespace std;

template <typename T, typename... Ts>
unique_ptr<T> my_make_unique(Ts&&... args){
    T * inst = new T(std::forward<Ts>(args)...);
    unique_ptr<T> uptr(inst);
    return uptr;
}

int main(){
    unique_ptr<int> p = my_make_unique<int>(5); 
    return 0;
}