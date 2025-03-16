#include <iostream>

using namespace std;

template <typename T, typename... Args>
T mymin(T a, Args... args){
    if constexpr (sizeof...(args)==0) 
        return a;
    else{ 
        T b=mymin(args...);
        return a<b?a:b;
    }
}

int main(){
    cout<<mymin(8,2,1,5,3,12)<<endl;
}