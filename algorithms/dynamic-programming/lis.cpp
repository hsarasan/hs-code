/*
Longest increasing subsequence (problem)
Given an array of integers arr, find the length of its longest increasing subsequence, 
its longest subsequence where each element is strictly greater than the previous one.
Example 1:
input:
arr = [7, 5, 2, 4, 7, 2, 3, 6, 4, 5, 12, 1, 7]
output: 5
explanation: A possible longest increasing subsequence is [2, 3, 4, 5, 7], its length is 5
Example 2:
input:
arr = [8, 5, 5, 3]
output: 1
explanation: The longest increasing subsequences that we can make are those that contain 
one element only, like [8]
Constraints:
len(arr) >= 1
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;
int lis(const vector<int> &nums){
    int n=nums.size();
    vector<int> dp(n,1);
    for (int i=1;i<n;++i){
        int lis=1;
        for (int j=1;j<i;++j)
        {
            if (nums[j]<nums[i]){
                lis=max(lis,1+dp[j]);
            }
        }
        dp[i]=lis;
    }
    return *max_element(dp.begin(), dp.end());
}

int main(){
    vector<int> arr = {7, 5, 2, 4, 7, 2, 3, 6, 4, 5, 12, 1, 7};
    cout<<lis(arr)<<endl;
    arr = {8,5,5,3};
    cout<<lis(arr)<<endl;
}