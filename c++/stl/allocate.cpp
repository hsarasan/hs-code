#include <bits/stdc++.h>

using namespace std;

template <typename T>
class LoggingAllocater : public std::allocator<T>{
    public:
    
        T * allocate(size_t n){
            cout<<"Request to allocate "<<n<<" bytes "<<endl;
            return std::allocator<T>::allocate(n);
        }
        
        
        void deallocate(T * ptr, size_t n){
            cout<<"Deallocating "<<n<<" objects of "<<sizeof(T)<<" size each "<<endl;
            std::allocator<T>::deallocate(ptr,n);
        }
        
};
int main(){
    vector<int, LoggingAllocater<int> > v;
    v.reserve(10);
    v.push_back(4);
    v.shrink_to_fit();
    v.pop_back();

    using myalloc=LoggingAllocater<pair<const int,string>> ; 
    map<int,string, less<int>, myalloc  > m;
    m[1]="one";
    m[2]="two";

}