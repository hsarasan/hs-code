#include <iostream>
#include <utility>

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
        A(A&& a){ std::cout<<"A(move)"<<std::endl; value=a.value; a.value=0;}
        ~A(){ std::cout<<"~A()"<<std::endl; }
        friend std::ostream & operator<< (std::ostream & o, const A & a);
};

std::ostream & operator<< (std::ostream & o, const A & a){
    o<<a.value;
    return o;
}

int main() {

    A a(3);
    A b(4);
    std::swap(a,b);
    std::cout<<a<<","<<b<<std::endl;
}
