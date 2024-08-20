#include <iostream>
#include <utility>
#include <cassert>

class Template{

        int value;
        virtual void execute()=0;
    public:
        void preexecute(){
            std::cout<<"preexecute"<<std::endl;
        }
        void postexecute(){
            std::cout<<"post execute"<<std::endl;
        }
        void operations(){
            preexecute();
            execute();
            postexecute();
        }
};

class Implementation: public Template {

    public:
        void execute() { std::cout<<"My execute "<<std::endl;}

};


int main() {
    Implementation impl;
    impl.operations();
}
