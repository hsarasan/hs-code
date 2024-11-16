#include <iostream>
#include <vector>

using namespace std;

template <typename L, typename R>
struct Adder{
    const L & l;
    const R & r;
    Adder(const L& left, const R& right):l(left),r(right){}
    auto operator[](size_t i) const { 
        return l[i]+r[i];
    }
    size_t size() const { return l.size(); };
};

template <typename L,typename R>
Adder<L,R> operator+(const L& l, const R& r){
    return Adder(l,r);
}

int main(){
    vector<int> v1{1,2,3,4,5};
    vector<double> v2{1.1,22,3.3,4.5,5};
    vector<int> v3{1,2,3,4,5};
    auto v = v1+v2+v3;
    for (int i=0;i<v.size();++i){
        cout<<v[i]<<endl;
    }
    return 0;
}