#include <bits/stdc++.h>

using namespace std;

int main(){
    vector<int> v{1,2,3,4,4,4,5,7,8};
    auto range=equal_range(v.begin(),v.end(),4);
    cout<<distance(range.first,range.second);
    return 0;
}