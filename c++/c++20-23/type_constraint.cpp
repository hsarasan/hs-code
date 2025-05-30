#include <iostream>

template <typename T>
concept Numeric=std::integral<T>||std::floating_point<T>;

void func(std::integral auto v){
    std::cout << v << std::endl;
}
void func2(Numeric auto v){
    std::cout << v << std::endl;
}


int main(){
    func(2);
    //func(2.9);
    //func("abc");
    func2(5);
    func2(2.9);
    //func2("abc");
    return 0;
}