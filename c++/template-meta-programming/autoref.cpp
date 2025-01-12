#include <iostream>
#include <memory>
#include <type_traits>

using namespace std;

struct X{};

void func(auto && x){
    cout<<"xxxx"<<endl;
    cout<<boolalpha<<is_rvalue_reference<decltype(x)>::value<<endl;
}
int main(){
    int i(10);
    func(i);
    func(10);
    return 0;
}