#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void partition(vector<int>& v, int lo, int hi){
    
    if (lo>=hi) return;
    int pivot=v[hi];
    int i=lo;
    int j=hi;
    while(i<j){
        if (v[i]<pivot) i++;
        else{
            while (v[j]>=pivot && j>i){
                j--;
            }
            if (j>i){
                std::swap(v[i],v[j]);
            }
        }
    }
    std::swap(v[i],v[hi]);
    partition(v,lo,i-1);
    partition(v,i+1,hi);
}

void sort(vector<int> v){
    copy(v.begin(), v.end(), ostream_iterator<int>(cout,","));
    cout<<endl;
    partition(v,0,v.size()-1);
    copy(v.begin(), v.end(), ostream_iterator<int>(cout,","));
    cout<<endl;
}
int main(){
    sort({8,3,9,4,2,5,1,5,6});
    sort({1,2,3,4,5});
    sort({4,3,2,1});
    return 0;
}