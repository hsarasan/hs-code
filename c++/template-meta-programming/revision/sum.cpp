#include <iostream>

using namespace std;

template <typename T, typename... Args>
T sum(T a, Args... args){
    if constexpr (sizeof...(args)==0){
        return a;
    }
    else{
        return a+sum(args...);
    }
}

int main(){
    cout<<sum(1,2,3,4)<<endl;
    return 0;
}