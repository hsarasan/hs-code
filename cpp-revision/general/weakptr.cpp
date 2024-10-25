#include <iostream>
#include <memory>

using namespace std;

struct X{
    int value;
};

int main() {
    
    auto sp=make_shared<X>();
    cout<<sp.use_count()<<endl;
    weak_ptr<X> wp=sp;
    auto sp2=wp.lock();
    cout<<sp.use_count()<<endl;
    sp.reset();
    cout<<sp2.use_count()<<endl;
    sp2.reset();
    cout<<wp.expired()<<endl;
    

    return 0;
}