#include <iostream>
#include <string>

using namespace std;

int allocated=0;
void * operator new(size_t size){
    cout<<"Request for "<<size<<" bytes "<<endl;
    allocated+=size;
    return malloc(size);
}
void operator delete(void * ptr){
    cout<<"Request for deletion of "<<ptr<<endl;
    free(ptr);
}

int main(){
    std::string s("walter white");
    cout<<"Stack size "<<sizeof(s)<<" Heap allocated="<<allocated<<" capacity="<<s.capacity()<<endl;
    s.append(" skyler ").append("jesse pinkman ").append(" hank ").append(" saul goodman ").append(" guz").append(" mike ");
    cout<<"Stack size "<<sizeof(s)<<" Heap allocated="<<allocated<<" capacity="<<s.capacity()<<endl;
}