#include <bits/stdc++.h>


using namespace std;

class Integer : public enable_shared_from_this<Integer>{
    int value;
    public:
        Integer(int i):value(i){}
};

int main(){
    auto i = new Integer(10);
    shared_ptr<Integer> ip(i);
    shared_ptr<Integer> ip2(i);
    auto ip3 = ip->shared_from_this();
    cout<<ip.use_count()<<endl;
    return 0;
}