/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product 
of all the elements of nums except nums[i].
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
You must write an algorithm that runs in O(n) time and without using the division operation.

Example 1:
Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
 
Constraints:

2 <= nums.length <= 105
-30 <= nums[i] <= 30
The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
*/
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;
class Solution {
    void fillupProduct(const vector<int>& nums, vector<int> & up){
        for (int i=nums.size()-2;i>=0; --i){
            up[i]=up[i+1]*nums[i+1];
        }
    }
    void filldownProduct(const vector<int> &nums, vector<int>& down){
        for (int i=1;i<nums.size();++i){
            down[i]=down[i-1]*nums[i-1];
        }
    }
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result(nums.size(),1);
        vector<int> up_product(nums.size(),1);
        vector<int> down_product(nums.size(),1);
        fillupProduct(nums,up_product);
        filldownProduct(nums,down_product);
        for (int i=0; i<nums.size(); ++i){
            result[i]=up_product[i]*down_product[i];
        }
        return result;
    }
};

int main(){
    vector<int> nums = {1,2,3,4};
    Solution sol;
    vector<int> result = sol.productExceptSelf(nums);
    vector<int> expected = {24,12,8,6};
    assert(result==expected);
    nums.clear();
    nums = {-1,1,0,-3,3};
    result = sol.productExceptSelf(nums);
    expected = {0,0,9,0,0};
    assert(result==expected);
    return 0;
}