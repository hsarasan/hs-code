#include <iostream>

using namespace std;

template <typename T>
class Base {
    public: 
        void interface(){
            static_cast<T*>(this)->implementation();
        }
};
class Derived: public Base<Derived>{
    public:
        void implementation(){
            cout<<"Derived::Implementation "<<endl;
        }
};

template <typename T>
void func(Base<T> & b){
    b.interface();
}

int main(){

    Derived d;
    func(d);
    return 0;
}