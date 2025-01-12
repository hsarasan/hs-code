#include <iostream>
#include <algorithm>

class Complex{
    int real;
    int imaginary;
    public:
        Complex(int _real, int _imag):real(_real),imaginary(_imag){}
        Complex(const Complex & )=default;
        Complex(Complex &&)=default;
        Complex & operator=(const Complex &)=default;
        operator int(){
            return real + imaginary;
        }
        //copy and swap
        Complex & operator=(Complex &&rhs){
            auto tmp(rhs);
            swap(tmp);
            return *this;
        }
        void swap(Complex & rhs){
            std::swap(rhs.imaginary,imaginary);
            std::swap(rhs.real,real);
        }
        friend const Complex  operator+(const Complex &a, const Complex & );
        Complex operator*(const Complex &rhs){
            std::cout<<"Special one "<<std::endl;
            return Complex (real+rhs.real,imaginary+rhs.imaginary);
        }
        friend std::ostream & operator<<(std::ostream & out, const Complex & c);
};

const Complex  operator+(const Complex &a, const Complex & b){
    std::cout<<"Inferior one "<<std::endl;
    return Complex(a.real+b.real, a.imaginary+b.imaginary);
}

std::ostream & operator<<(std::ostream & out, const Complex & c){
    out<<c.real<<" + i "<<c.imaginary;
    return out;
}

int main(){
    Complex a(2,3);
    Complex b(4,7);
    auto c = a + b;   
    auto d = std::move(c);
    std::cout<<c<<std::endl;
    std::cout<<d<<std::endl;
    d = std::move(a);
    std::cout<<d<<std::endl;
    std::cout<<a<<std::endl;
    c=a=b;
    std::cout<<a<<"=>"<<b<<"=>"<<c<<std::endl;
    std::cout<<b<<","<<d<<std::endl;
    b.swap(d);
    std::cout<<b<<","<<d<<std::endl;
    std::cout<<b<<","<<b<<std::endl;
    b.swap(b);
    std::cout<<b<<","<<b<<std::endl;
    std::cout<<b<<","<<c<<std::endl;
    c=b;
    std::cout<<b<<","<<c<<std::endl;
    b=b;
    std::cout<<b<<","<<c<<std::endl;
    int bi = b;   
    std::cout<<bi<<std::endl;
    return 0;
}