/*
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
*/

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
class Solution {
    template <typename iter>
    void reverse_(iter begin, iter end){
        iter rbegin=end-1;
        while (begin<rbegin){
            std::iter_swap(begin++,rbegin--);
        }   
    }
public:
    void rotate(vector<int>& nums, int k) {
        int n=nums.size();
        k=k%n;
        reverse_(nums.begin(),nums.begin()+n-k);
        reverse_(nums.begin()+n-k, nums.end());
        reverse_(nums.begin(), nums.end());
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,2,3,4,5,6,7};
    s.rotate(nums, 3);
    assert(nums == vector<int>({5,6,7,1,2,3,4}));
    nums = {-1,-100,3,99};
    s.rotate(nums, 2);
    assert(nums == vector<int>({3,99,-1,-100}));
    return 0;
}