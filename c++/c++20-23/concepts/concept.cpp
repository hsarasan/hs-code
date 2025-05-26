#include <iostream>

using namespace std;

template <typename T>
requires (is_pointer_v<T>)
auto max_v(T a, T b){
    cout<<"pointer max"<<endl;
    return *a<*b?*b:*a;
}

template <typename T>
requires (!is_pointer_v<T>)
auto max_v(T a, T b){
    cout<<"non_ptr max"<<endl;
    return a<b?b:a;
}

int main(){
    cout<<max_v(5,2)<<endl;
    int a=5;
    int b=7;
    int& a_ref=a;
    int& b_ref=b;
    cout<<max_v(a,b)<<endl;
    cout<<max_v(&a,&b)<<endl;
    cout<<max_v(a_ref, b_ref)<<endl;
    return 0;
}