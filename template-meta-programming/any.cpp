#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>
#include <any>

using namespace std;

struct X{
    void show(){ cout<<"show"<<endl;}
};

void execute(std::any & a){
    if (a.has_value()){
        try{
            auto x = any_cast<X>(a);
            x.show();
        }
        catch(std::exception & e){
            cerr<<"Exception is "<<e.what()<<endl;
        }
    }
}

int main(){
    std::any a;
    X x;
    a = x;
    execute(a);
    a = 5;
    execute(a);
    return 0;
}