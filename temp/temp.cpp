#include <iostream> 
#include <functional>

using namespace std;

template <typename T>
struct my_shared_ptr{
    my_shared_ptr(){
        ref_count=nullptr;
        ptr=nullptr;
    }
    my_shared_ptr(T* ptr){
        ref_count=new int(1);
    }
    my_shared_ptr(const my_shared_ptr& other){
        (*other.ref_count)++;
        ref_count=other.ref_count;
        ptr=other.ptr;
    }
    my_shared_ptr& operator=(const my_shared_ptr& other){
        if (&other==this) return *this;
        release();
        ref_count=other.ref_count;
        ptr=other.ptr;
        (*other.ref_count)++;
        return *this;
    }
    my_shared_ptr(my_shared_ptr&& other) noexcept{
        ref_count=other.ref_count;
        ptr=other.ptr;
        other.ptr=nullptr;
        other.ref_count=nullptr;
    }
    my_shared_ptr& operator=(my_shared_ptr&& other) noexcept{
        if (&other==this) return *this;
        release();
        ref_count=other.ref_count;
        ptr=other.ptr;
        other.ref_count=nullptr;
        other.ptr=nullptr;
        return *this;
    }
    ~my_shared_ptr(){
        cout<<"Usage Count "<<*ref_count<<endl;
        release();
    }
    private:
        int * ref_count{nullptr};
        T * ptr{nullptr};
        std::function<void(T*)> deleter;
        void release(){
            if (!ref_count) return;
            (*ref_count)--;
            if (*ref_count==0){
                if (ptr){
                    delete ptr;
                }
                delete ref_count;
            }
        }
};

int main(){

    my_shared_ptr<int> msp(new int(1));
    auto msp2=msp;
    my_shared_ptr<int> mx(new int(2));
    msp2=mx;
    auto msp3=mx;
    return 0;
}



