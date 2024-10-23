#include <bits/stdc++.h>


using namespace std;

class Integer : public enable_shared_from_this<Integer>{
    int value;
    public:
        Integer(int i):value(i){}
};

int main(){
    auto i = make_shared<Integer>(10);
    auto iShPtr = i->shared_from_this();
    cout<<iShPtr.use_count()<<endl;
    return 0;
}