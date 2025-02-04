/*
You are given an integer array nums that is sorted in non-decreasing order.

Determine if it is possible to split nums into one or more subsequences such that both of the 
following conditions are true:

Each subsequence is a consecutive increasing sequence (i.e. each integer is exactly one more than 
the previous integer). All subsequences have a length of 3 or more.
Return true if you can split nums according to the above conditions, or false otherwise.

A subsequence of an array is a new array that is formed from the original array by deleting some 
(can be none) of the elements without disturbing the relative positions of the remaining elements. 
(i.e., [1,3,5] is a subsequence of [1,2,3,4,5] while [1,3,2] is not).

 

Example 1:

Input: nums = [1,2,3,3,4,5]
Output: true
Explanation: nums can be split into the following subsequences:
[1,2,3,3,4,5] --> 1, 2, 3
[1,2,3,3,4,5] --> 3, 4, 5
Example 2:

Input: nums = [1,2,3,3,4,4,5,5]
Output: true
Explanation: nums can be split into the following subsequences:
[1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
[1,2,3,3,4,4,5,5] --> 3, 4, 5
Example 3:

Input: nums = [1,2,3,4,4,5]
Output: false
Explanation: It is impossible to split nums into consecutive increasing subsequences of length 3 or
 more.
 */

// Solution 1: Greedy
#include <vector>   
#include <unordered_map>
#include <queue>
#include <iostream>
#include <cassert>
using namespace std;


class Solution {
public:
    bool isPossible(vector<int>& nums) {
        unordered_map<int,priority_queue<int,vector<int>,std::greater<int>>> length_pq;
        for (int num: nums){
            if (length_pq.count(num-1)==0){
                length_pq[num].push(1);
                continue;
            }
            auto &prevQ=length_pq[num-1];
            int shortest_seq_length=prevQ.top();
            prevQ.pop();
            if (prevQ.size()==0) length_pq.erase(num-1);
            length_pq[num].push(shortest_seq_length+1);
        }
        for (const auto &[key,value]: length_pq){
            if (value.top()<3) return false;
        }
        return true;
    }
};

int main(){
    vector<int> nums={1,2,3,3,4,5};
    Solution sol;
    bool res=sol.isPossible(nums);
    nums={1,2,3,3,4,4,5,5};     
    res=sol.isPossible(nums);
    assert(res==true);
    nums={1,2,3,4,4,5};
    res=sol.isPossible(nums);
    assert(res==false);
    nums={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    res=sol.isPossible(nums);
    assert(res==true);
    return 0;
}