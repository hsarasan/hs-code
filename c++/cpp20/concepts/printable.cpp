#include <iostream>

using namespace std;

template <typename T>
concept printable=requires(std::ostream& os, const T&a){
    {os<<a}->same_as<std::ostream&>;
};

template <printable T>
void print(const T& a){
    cout<<a;
}

int main(){
    cout<<5<<endl;
    return 0;
}