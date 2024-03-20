#include <vector>
#include <iostream>

template <typename T, typename... Types>
void set(Types... args){
    std::vector<T> v{args...};
}
template <typename... Types>
auto add(Types... args){
    return (0 + ... + args);
}
template <typename... Types>
void print(Types... args){
    (std::cout<<...<<args);
}

int main(){
    set<int>(1,2,3);
    auto sum=add(1,2,3,4,5);
    print(1,4,34,3);
    return 0;
}