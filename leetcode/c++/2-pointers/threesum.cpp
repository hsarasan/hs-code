#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <algorithm>

using namespace std;

class Solution {


public:
    vector<vector<int>> threeSum(vector<int> nums) {
        sort(nums.begin(), nums.end());
        int n=nums.size();
        int i=0;
        vector<vector<int>> result;
        set<vector<int>> result_set;
        

        while(i<n-2 && nums[i]<=0){
            int j=i+1;
            int k=n-1;
            while(j<k){
                int sum=nums[i]+nums[j]+nums[k];
                if (sum==0){
                    result_set.insert({nums[i],nums[j],nums[k]});
                    j++;
                }
                else if (sum<0){
                    j++;
                }
                else{
                    k--;
                }
            }
            i++;
        }
        return {result_set.begin(), result_set.end()};
    }
};


int main(){
    Solution s;
    vector<vector<int>> res=s.threeSum({-1,0,1,2,-1,-4});
    vector<vector<int>> expected{ {-1,0,1}, {-1,-1,2} };
    sort(res.begin(), res.end());
    sort(expected.begin(), expected.end());
    assert(res==expected);
    return 0;
}