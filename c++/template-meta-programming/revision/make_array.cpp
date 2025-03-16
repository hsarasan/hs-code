#include <iostream>
#include <array>
#include <type_traits>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>

using namespace std;

string demangle(const char* name) {
    int status = 0;
    unique_ptr<char[], void(*)(void*)> demangled(abi::__cxa_demangle(name, nullptr, nullptr, &status), free);
    return (status == 0) ? demangled.get() : name;
}

template <typename... Args>
auto make_array(Args... args){
    return array<common_type_t<Args...>,sizeof...(Args)>{args...};
}

int main(){
    auto x=make_array(1.2,2,3.1,'1');
    cout<<demangle(typeid(x).name())<<endl;
    return 0;
}