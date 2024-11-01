#include <iostream>

struct X{
    int value;
    X(int x):value(x){}
};
struct Y{
    long value;
    Y(){ value=0;}
    Y(const X& x){
        value=x.value+10;
    }
};


using namespace std;

int main(){
    X x(20);
    Y y = static_cast<Y>(x);
    cout<<y.value<<endl;
    return 0;
}