#include <iostream>

class X{
    public:
        virtual void f(){}

};
class Y: public X{

};
int main(){
    X x;
    Y y;
    auto x_t = type_info(x);
    return 0;
}