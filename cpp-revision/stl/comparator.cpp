#include <iostream>
#include <unordered_set>
#include <set>

using namespace std;



struct Complex{
    int real,imag;
    Complex(int real_, int imag_):real(real_),imag(imag_){}
    bool operator<(const Complex & c) const { 
        return real<c.real || ( real==c.real && imag<c.imag);   
    }
    friend ostream & operator<<(ostream & o, const Complex & c){
        o<<c.real<<" + "<<c.imag<<"i";
        return o;
    }
};

struct comparator{

    bool operator() (const Complex & left, const Complex & right ) const {
        return left.imag<right.imag;
    }  

};

int main(){
    set<Complex, comparator> S;
    S.insert(Complex(3,1));
    S.insert(Complex(3,3));
    S.insert(Complex(1,1));
    S.insert(Complex(1,2));
    S.insert(Complex(2,1));
   
    for (const auto & c: S) cout<<c<<endl;
    return 0;
}