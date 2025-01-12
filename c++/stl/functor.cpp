#include <bits/stdc++.h>

using namespace std;

struct ThirdElementRemover{
    mutable int thirdElement{0};
    bool operator()(const int &i) const{
        
        thirdElement++;
        return thirdElement%3==0;
    }
};

int main(){
    vector<int> v{1,2,3,4,5,6,7,8,9,10};
    ThirdElementRemover removeThird;
    auto iter=remove_if(v.begin(), v.end(), removeThird);
    v.erase(iter,v.end());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout,","));
    cout<<endl;
}



