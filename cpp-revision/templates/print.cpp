#include <iostream>

using namespace std;

void print(){
    return ;
}

template <typename T,typename... Ts>
void print(T arg, Ts... args){
    cout<<arg;
    print(args...);
}

using namespace std;
int main(){
    print(1,"abc");
    return 0;

}