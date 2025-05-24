#include <vector>
#include <algorithm>
#include <iostream>
#include <compare>

using namespace std;

int main(){
    vector<int> v1{12,4,6};
    vector<int> v2{12,4,9};
    cout<<ranges::lexicographical_compare(v1,v2)<<endl;
    auto x = lexicographical_compare_three_way(v1.begin(),v1.end(),v2.begin(),v2.end());
    x<0?cout<<"less":cout<<"greater or equal "<<endl;
    return 0;
}