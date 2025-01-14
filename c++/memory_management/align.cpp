#include <iostream>

struct Misaligned{
    char c;
    int i;  
    char c2;
};
struct Aligned{
    int i;
    char c;
    char c2;
};

int main(){
    std::cout << "int "<<alignof(int) << std::endl;
    std::cout << "char "<<alignof(char) << std::endl;
    std::cout << "double "<<alignof(double) << std::endl;
    std::cout << "long "<<alignof(long) << std::endl;
    std::cout << "long long "<<alignof(long long) << std::endl;
    std::cout << "float "<<alignof(float) << std::endl;
    std::cout << "short "<<alignof(short) << std::endl;
    std::cout << "long double "<<alignof(long double) << std::endl;
    std::cout << "char16_t "<<alignof(char16_t) << std::endl;
    std::cout << "char32_t "<<alignof(char32_t) << std::endl;
    std::cout << "void* "<<alignof(void*) << std::endl;
    std::cout << "Misaligned "<<alignof(Misaligned) << std::endl;
    std::cout << "Aligned "<<alignof(Aligned) << std::endl;

    std::cout<<sizeof(Misaligned)<<std::endl;
    std::cout<<sizeof(Aligned)<<std::endl;  
    return 0; 
}