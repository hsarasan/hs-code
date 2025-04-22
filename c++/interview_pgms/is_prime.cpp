#include <iostream>

using namespace std;

bool is_prime(int n, int i=2){
    if (n==1) return false;
    if (n==2) return true;
    if (n<i*i) return true;
    if (n%i==0) return false;
    return is_prime(n,i+1);
}

int main(){
    cout<<is_prime(29)<<endl;
    cout<<is_prime(27)<<endl;
    return 0;
}