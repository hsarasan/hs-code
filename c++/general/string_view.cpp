#include <iostream>
#include <string>

using namespace std;

void f(std::string_view s){
    cout<<"sv"<<s<<endl;
}

int main(){
    f("abc");
}