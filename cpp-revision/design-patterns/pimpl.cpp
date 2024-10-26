#include "pimpl.h"
#include <iostream>

using namespace std;

class Implementation{

    public:
        void execute(){
            cout<<"Implementation::execute()"<<endl;
        }
};

void Interface::execute(){
    pImpl->execute();
}

int main(){

    Interface interface( move(make_unique<Implementation>()));
    interface.execute();
}