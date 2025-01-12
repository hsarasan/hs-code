#include <iostream>
#include <utility>
#include <cassert>
#include <vector>

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
        virtual int get_value() const{return value;}
        friend std::ostream & operator<< (std::ostream & o, const A & a);
};

class B: public A {

    long value;
    public:
        B(int val): A(val){};
};

std::ostream & operator<< (std::ostream & o, const A & a){
    o<<a.value;
    return o;
}

std::vector<A*> v;

int main() {
    A * a  = new A(5);
    B * b = new B(50);
    v.push_back(a);
    v.push_back(b);
    B * b2 = dynamic_cast<B*>(v[1]);
    assert (b2!=nullptr);
    B * a2 = dynamic_cast<B*>( v[0] );
    assert(a2==nullptr);
}
