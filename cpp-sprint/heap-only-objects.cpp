#include <iostream>


class HeapOnly{
    ~HeapOnly() { std::cout<<"~HeapOnly"<<std::endl;}
    public:
    HeapOnly(){ std::cout<<"HeapOnly "<<std::endl;}
    void destroy() { this->~HeapOnly();}
};


int main() {

    HeapOnly * hp = new HeapOnly();
    hp->destroy();

}