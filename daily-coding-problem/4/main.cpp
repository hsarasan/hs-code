#include <iostream>
#include <unordered_set>
#include <vector>
#include <cassert>

using namespace std;

int getLeftMostMissingPositive(vector<int>& nums){
    unordered_set<int> S;
    int missing=2;
    for (auto num: nums){
        if (num>0){
            if (num==missing){
                int search=num+1;
                while(S.count(search)!=0){
                    search++;
                }
                missing=search;
            }
            S.insert(num);
        }
    }
    return missing;
}

int main(){
    vector<int> nums={3,4,-1,1};
    assert(getLeftMostMissingPositive(nums)==2);
    nums={1,2,0};
    assert(getLeftMostMissingPositive(nums)==3);
    return 0;
}