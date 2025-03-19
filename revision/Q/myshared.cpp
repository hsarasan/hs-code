#include <iostream>


using namespace std;

template <typename T>
class SharedPtr{
        T * _pointer;
        int * _count;
    public:
        SharedPtr()=delete;
        explicit SharedPtr(T* ptr):_pointer(ptr),_count(new int(1)){}
        SharedPtr(const SharedPtr& other){
            _pointer=other._pointer;
            _count=other._count;
            (*_count)++;
        }
        SharedPtr(SharedPtr && other) noexcept{
            _pointer=other._pointer;
            _count=other._count;
            other._count=nullptr;
            other._pointer=nullptr;
        }
        ~SharedPtr(){
            (*_count)--;
            if ((*_count)==0) {
                delete _pointer;
            }
        }
        T * operator->(){
            return _pointer;
        }
        T& operator*(){
            return *_pointer;
        }

};


int main(){
    return 0;
}