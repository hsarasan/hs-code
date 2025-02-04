/*
1. Two Sum
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> hashmap;
        for (int i=0; i<nums.size(); ++i)
            hashmap[nums[i]]=i;
        for (int i=0; i<nums.size(); ++i){
            if (hashmap.count(target-nums[i])>0){
                int idx=hashmap[target-nums[i]];
                if (idx!=i){
                    return {idx,i};
                }
            }
        }
        return {};    
    }
};