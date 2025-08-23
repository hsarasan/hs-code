#include <iostream>

using namespace std;

template <typename T>
struct Base{
    void interface(){
        static_cast<T*>(this)->impl();
    }
};

struct Derived: public Base<Derived>{
    void impl(){
        cout<<"Derived impl"<<endl;
    }
};

template <typename T>
void func(Base<T> &b){
    b.interface();
}

int main(){
    Derived d;
    func(d);
    return 0;
}