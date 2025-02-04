
/*
 First Missing Positive
Solved
Hard
Topics
Companies
Hint
Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.

You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

Example 1:

Input: nums = [1,2,0]
Output: 3
Explanation: The numbers in the range [1,2] are all in the array.
Example 2:

Input: nums = [3,4,-1,1]
Output: 2
Explanation: 1 is in the array but 2 is missing.
Example 3:

Input: nums = [7,8,9,11,12]
Output: 1
Explanation: The smallest positive integer 1 is missing.
 
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        priority_queue<int, std::vector<int>, std::greater<int>> PQ (nums.begin(), nums.end());
        int expected=1;
        while(!PQ.empty()){
            int num=PQ.top();
            if (num>0) {
                if (num>expected) return expected;
                if (num==expected) expected++;
                
            }
            PQ.pop();
        }
        return expected;
    }
};

int main(){
    Solution s;
    vector<int> nums{1,2,0};    
    assert(s.firstMissingPositive(nums)==3);
    nums={3,4,-1,1};
    assert(s.firstMissingPositive(nums)==2);
    nums={7,8,9,11,12};
    assert(s.firstMissingPositive(nums)==1);
    return 0;
}