#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;
using namespace std::placeholders;

int add(int a, int b){ return a+b;}

int main(){
    auto add5=std::bind(add,5, placeholders::_1);
    cout<<add5(10)<<endl;
    return 0;
}