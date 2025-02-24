#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

vector<int> getProduct(vector<int> arr){
    int n = arr.size();
    vector<int> down(n,1);
    vector<int> up(n,1);
    vector<int> result(n,1);
    for ( int i=1;i<n;++i){
        down[i]=down[i-1]*arr[i-1];
    }
    for (int i=n-2;i>=0;--i){
        up[i]=up[i+1]*arr[i+1];
    }
    for (int i=0;i<n;++i){
        result[i]=down[i]*up[i];
    }
    return result;
}


int main(){
    vector<int> arr = {1,2,3,4};
    vector<int> result = getProduct(arr);
    vector<int> expected = {24,12,8,6};
    assert(result==expected);
    result = getProduct({1,2,3,4,5});
    expected = {120,60,40,30,24};
    assert(result==expected);
    return 0;
}