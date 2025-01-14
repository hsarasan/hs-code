#include <iostream>

void func(std::byte *stack_begining){
    std::byte data[1024];
    std::cout<<stack_begining-data<<std::endl;
    func(stack_begining);
}

void f(){
    std::byte b;
    func(&b);

}

int main(){
    f();
}