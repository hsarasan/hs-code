/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
*/

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> prefix(nums.size());
        prefix[0]=1;
        for (int i=1;i<n;++i)
        {
            prefix[i] = prefix[i-1]* nums[i-1];
        }
        //now prefix * suffix
        for(const auto  & item: prefix)
        {
            std::cout<<item<<" ";
        }
        std::cout<<std::endl;
        int suffix = 1;
        for (int i=n-1;i>=0;--i)
        {
            prefix[i] = prefix[i] * suffix;
            suffix = suffix * nums[i];
        }
        return prefix;
    }
};

int main() {

    std::vector<int> v,r;
    Solution s;
    v = {1,2,3,4};
    r = {24,12,8,6};
    assert(s.productExceptSelf(v)== r);
    v = {-1,1,0,-3,3};
    r = {0,0,9,0,0};
    assert(s.productExceptSelf(v)== r);

    return 0;

}