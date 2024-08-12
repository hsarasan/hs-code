#include <iostream>

class Complex{
    int real;
    int imag;
    public:
        Complex():real(0),imag(0){
            std::cout<<"C"<<std::endl;
        }
        Complex(int real, int imag):real(real),imag(imag){
            std::cout<<"C(int,int)"<<std::endl;
        }
        Complex(const Complex & c) { 
            std::cout<<"C(const Complex &)"<<std::endl;
            real = c.real;
            imag = c.imag;
        }
        Complex & operator=(const Complex &c){
            std::cout<<"operator=(const Complex &)"<<std::endl;
            real = c.real;
            imag = c.imag;
            return *this;
        }
        Complex(Complex && c){
            std::cout<<"C(Complex &&)"<<std::endl;
            int temp(c.imag);
            std::swap(temp,imag);
            temp=c.real;
            std::swap(temp,real);
        }
        Complex& operator=(Complex &&c){
            std::cout<<"operator=(Complex &&)"<<std::endl;
            int temp(c.imag);
            std::swap(temp,imag);
            temp=c.real;
            std::swap(temp,real);
            return *this;
        }
        ~Complex() noexcept{
            std::cout<<"~C"<<std::endl;
        }
        friend const Complex   operator+(Complex& lhs, Complex & rhs);
        friend std::ostream & operator<<(std::ostream &o, const Complex &c);
};
const Complex  operator+(Complex& lhs, Complex & rhs){
    return Complex(lhs.real+rhs.real, lhs.imag+rhs.imag);
}
std::ostream & operator<<(std::ostream &o, const Complex &c){
    o<<c.real<<"+i"<<c.imag;
    return o;
}

int main(){
    Complex c1(1,2);
    auto c2 = c1;
    auto c3 = c2;
    auto c4 = std::move(c1);
    c3  = std::move(c1);
    auto c5 = c1+c2;
    std::cout<<c5<<std::endl;
}