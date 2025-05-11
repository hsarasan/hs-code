#include <iostream>
#include <iomanip>

using namespace std;

class Complex {

    Complex(const double real, const double imag):real(real), imag(imag) {}
    Complex():real(0), imag(0) {}
    Complex(Complex&& c) noexcept {
        real = c.real;
        imag = c.imag;
    }
    Complex& operator=(Complex&& c) noexcept {
        if (this==&c) return *this;
        real = c.real;
        imag = c.imag;
        return *this;
    }
    Complex(const Complex& c) = default;
    Complex& operator=(Complex&)=default;
    ~Complex() = default;

    private:
        double real;
        double imag;
};


int main() {
    constexpr bool flag = true;
    cout<<std::boolalpha<<flag<<endl;
    return 0;
}