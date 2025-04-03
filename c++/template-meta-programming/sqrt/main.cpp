#include <iostream>
#include <array>

using namespace std;

template <typename T>
constexpr auto sqrt(T n){
    if (n<=1){
        return 1;
    }
    T lo=1;
    T high=n;

    T mid;
    while(lo<=high){
        mid=(lo+high)/2;
        if (mid*mid==n) return mid;
        //if (lo==high-1) return mid;
        if (mid*mid<n){
            lo=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return mid;
}


int main(){
    cout<<sqrt(25)<<endl;
    cout<<sqrt(23)<<endl;
    
    cout<<sqrt(35)<<endl;
    
    cout<<sqrt(36)<<endl;

    static_assert(sqrt(49)==7);
    std::array<int,sqrt(64)> a;
    cout<<a.size()<<endl;
    
    return 0;
}