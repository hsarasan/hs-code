#include <iostream>
#include <string>

class A {
public:
    A(int i) {std::cout<<"A::A(int)"<<std::endl;}
    A(std::string  i) {std::cout<<"A::A(string)"<<std::endl;}

    //mandatory default constructor
    A(){std::cout<<"default A()"<<std::endl;}
    int x;
};

class B : public virtual A {
    public:
        B():A(1){}
};

class C : public virtual A {
        public:
        C():A("abc"){}
};

class D : public B, public C {
    public:
    D(){}
};

int main(){

    D d;
}