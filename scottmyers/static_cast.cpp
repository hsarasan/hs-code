#include <iostream>
#include <utility>
#include <cassert>

class A{

    int value;
    public:
        A(int _value):value(_value){ std::cout<<"A()=>"<<value<<std::endl; }
        A(const A& a){ std::cout<<"A(copy)"<<std::endl; 
            value=a.value;
        }
        A& operator=(const A& a){ std::cout<<"A(operator=)"<<std::endl; 
            value=a.value;
            return *this;
        }
        A& operator=(A&& a){ std::cout<<"A(operator= move)"<<std::endl; 
            value=a.value;
            return *this;
        }
        A(A&& a){ std::cout<<"A(move)"<<std::endl; value=a.value; a.value=0;}
        ~A(){ std::cout<<"~A()"<<std::endl; }
        int get_value() const{return value;}
        friend std::ostream & operator<< (std::ostream & o, const A & a);
};

class B {

    long value;
    public:
        B(const A& a){
            value=a.get_value();
            std::cout<<"Inside B()"<<std::endl;
        }
        bool operator==(const B& b) const{
            return value==b.value;
        }
};

class C{
    int value;
    public:

};
std::ostream & operator<< (std::ostream & o, const A & a){
    o<<a.value;
    return o;
}

int main() {
    A a(10);
    B b(a);
    B b2=static_cast<B>(a);
    assert(b==b2);
}
