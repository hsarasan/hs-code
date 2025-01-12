#include <iostream>
#include <cassert>
#include <new>

void outOfMemory(){
    std::cout<<"Ran out of memory "<<std::endl;
    exit(1);
}

int main(){
    std::set_new_handler(outOfMemory);
    auto * p = new char[9999999999999999];
    assert(p);
}