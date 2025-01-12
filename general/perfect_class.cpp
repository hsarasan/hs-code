#include <iostream>
#include <utility> // For std::swap
#include <cstring> // For std::strlen, std::strcpy
#include <cassert>

class Resource {
private:
    char* data;
    std::size_t size;

public:
    // 1. Default Constructor
    Resource() : data(nullptr), size(0) {
        std::cout << "Default Constructor called\n";
    }

    // 2. Parameterized Constructor
    Resource(const char* str) {
        std::cout << "Parameterized Constructor called\n";
        size = std::strlen(str);
        data = new char[size + 1];
        std::strcpy(data, str);
    }

    // 3. Destructor
    ~Resource() {
        delete[] data;
    }

    // 4. Copy Constructor
    Resource(const Resource& other){ 
        std::cout << "Copy Constructor called\n";
        if (other.data) {
            data = new char[other.size + 1];
            std::strcpy(data, other.data);
            size=other.size;
        }
    }

    // 5. Copy Assignment Operator (Using Copy-and-Swap Idiom)
    Resource& operator=( const Resource & other) {
        std::cout<<"Copy assignment called "<<std::endl;
        Resource temp=other;
        swap(*this,temp);
        return *this;
    }

    // 6. Move Constructor
    Resource(Resource&& other) noexcept {
        std::cout << "Move Constructor called\n";
        data=nullptr;
        size=0;
        swap(*this,other);
    }

    // 7. Move Assignment Operator (Using Swap)
    Resource& operator=(Resource&& other) noexcept {
        std::cout << "Move Assignment Operator called\n";
        Resource temp = std::move(other);
        swap(*this, temp);
        return *this;
    }

    // Friend Swap Function
    friend void swap(Resource& first, Resource& second) noexcept {
        using std::swap; // Enable ADL (Argument-Dependent Lookup)
        swap(first.data, second.data);
        swap(first.size, second.size);
    }


    char * getData() const{
        return data;
    }
    int getSize() const{
        return size;
    }
};

void verify(const Resource &r, const std::string &s, int size){
    auto str = r.getData();
    auto sz = r.getSize();
    assert(str==std::string("Hello, World!"));
    assert(sz==size);
}

void verify_null(const Resource &r){
    assert(r.getData()==nullptr);
    assert(r.getSize()==0);
}
int main() {

    std::cout<<"TC for normal construction"<<std::endl;
    Resource res1("Hello, World!");
    verify(res1,"Hello, World!",13);
    std::cout<<"===== done ========"<<std::endl;

    std::cout<<"TC for copy construction "<<std::endl;
    Resource res2 = res1; // Calls Copy Constructor
    verify(res2,"Hello, World!",13);
    verify(res1,"Hello, World!",13); 
    std::cout<<"======= done ======"<<std::endl;

    std::cout<<"TC for copy assignment"<<std::endl;
    Resource res3;
    res3 = res1; // Calls Copy Assignment Operator
    verify(res3,"Hello, World!",13);
    verify(res1,"Hello, World!",13);
    std::cout<<"====== done ======="<<std::endl;
 
    std::cout<<"Test case for move ctor "<<std::endl;
    Resource res4 = std::move(res1); // Calls Move Constructor
    verify(res4,"Hello, World!",13);
    verify_null(res1);
    std::cout<<"======= done ======"<<std::endl;
 
    std::cout<<"Test case for move assignment "<<std::endl;
    Resource res5;
    res5 = std::move(res2); // Calls Move Assignment Operator
    verify(res5,"Hello, World!",13);
    verify_null(res2);
    std::cout<<"======= done ====="<<std::endl;
    return 0;
}