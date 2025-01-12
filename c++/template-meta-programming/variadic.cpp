#include <iostream>


void print()
{
    std::cout<<"empty print "<<std::endl;
}
template<typename T, typename... Args>
void print(T t, Args... params) {
    std::cout<<t<<" ";
   print(params...);
}

template <typename T>
void print(T t){
    std::cout<<"one arg one "<<t<<std::endl;
}

template <typename... Args>
void foldprint(Args... args){
    (std::cout<<...<<args);
}

template <typename... Args>
auto foldaccumulate(Args... args){
    return (0 + ... + args);
}

int main() {

    print(1,2,"skfd");
    print(9);
    foldprint(1,5,"xyz");
    auto x = foldaccumulate(1,2.4,52.4);
    std::cout<<std::endl;
    std::cout<<x<<std::endl;
}