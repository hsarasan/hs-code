#include <iostream>


void print()
{

}
template<typename T, typename... Args>
void print(T t, Args... params) {
    std::cout<<t;
   print(params...);
}


int main() {

    print(1,2,"skfd");
}