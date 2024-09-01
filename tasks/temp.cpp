#include <iostream>

struct X{

    void buildX1(){std::cout<<"building x1 "<<std::endl;}
    void buildX2(){std::cout<<"building x2 "<<std::endl;}
};

X f(X &x){
    x.buildX1();
    return x;
}
void g(X &x){
    x.buildX2();
}

int main(){
    X x;
    f(x).buildX2();
}