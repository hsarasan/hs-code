#include <iostream>

template <typename T>
class Base{
    public:
    void f(){
        static_cast<T*> (this)->f2();
    }
};

class Derived: public Base<Derived>{
    public:
    void f2(){
        std::cout<<"Derived:f()"<<std::endl;
    }
};
class Derived2: public Base<Derived2>{
    public:
    void f2(){
        std::cout<<"Derived2:f()"<<std::endl;
    }
};

int main(){
    Derived d;
    d.f();
    Derived2 d2;
    d2.f();
}