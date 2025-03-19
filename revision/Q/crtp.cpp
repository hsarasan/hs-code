#include <iostream>

using namespace std;

template <typename T>
class Base{

    public:

    void interface(){
        auto ptr=static_cast<T*>(this);
        ptr->implementation();
    }
};
class Derived: public Base<Derived>{
    public:
        void implementation(){
            cout<<"From Implementation "<<endl;
        }
};

int main(){
    Derived d;
    d.interface();
    return 0;
}