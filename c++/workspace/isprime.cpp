#include <iostream>

using namespace std;


constexpr bool isPrime(int n, int i=2) {
    if (n < 2) return false;        // Numbers less than 2 are not prime
    if (n % i == 0) return false;   // If n is divisible by i, it's not prime
    if ( i * i > n) return true;     // If i^2 > n, we have checked all divisors
    return isPrime(n,i+1);     // Recursive call to check next divisor (i+1)
}
/*
template <int n,int i=2>
constexpr bool isPrime(){
    if (n<2) return false;
    if (n%i==0) return false;
    if ( i*i>n ) return true;
    return isPrime<n,i+1> ();
}
*/

int main(){
    cout<<isPrime(29)<<endl;
    cout<<isPrime(27)<<endl;
    return 0;
}