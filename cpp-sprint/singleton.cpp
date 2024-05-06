#include <iostream>

class X{

    X(){ std::cout<<this<<std::endl; }
    X(const X& )=delete;
    public:
        void execute() { std::cout<<"X::execute" << this <<std::endl;}
        static X& instance(){
            static X instance;
            return instance;
        }
};

int main() {
    X::instance().execute();
}