#include <iostream>
#include <memory>

class Foo{
public:
    void *operator new(size_t size){
        std::cout << "new operator overloaded" << std::endl;
        return ::operator new(size);
    }
    void operator delete(void *p){
        std::cout << "delete operator overloaded" << std::endl;
        ::operator delete(p);
    }
};

int main(){
    auto foo = std::make_unique<Foo>();
}