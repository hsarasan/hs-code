/*

You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int assured{0};
        int n = nums.size();
        for (int i=0;i<n-1;++i)
        {
            if (assured<i) return false;
            assured = std::max(assured, i+nums[i]);
        }
        return assured>n-2;
    }
};

int main() {
    std::vector<int> nums;
    Solution s;
    nums = {2,3,1,1,4};
    bool canJump = s.canJump(nums);
    std::cout<<canJump<<std::endl;
    nums = {3,2,1,0,4};
    canJump = s.canJump(nums);
    std::cout<<canJump<<std::endl;
    nums = {0,2,3};
    canJump = s.canJump(nums);
    std::cout<<canJump<<std::endl;

}