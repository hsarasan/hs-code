/*
977. Squares of a Sorted Array
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.
*/
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> result;
        result.reserve(nums.size());
        auto iter=std::lower_bound(nums.begin(), nums.end(),0);
        int idx=std::distance(nums.begin(),iter);
        
        int left_idx=idx-1;
        int right_idx=idx;
        bool done=left_idx<0 || right_idx==nums.size();
        while(!done){
            if (abs(nums[left_idx])<nums[right_idx]){
                result.push_back(nums[left_idx]*nums[left_idx]);
                left_idx--;
            }
            else{
                result.push_back(nums[right_idx]*nums[right_idx]);
                right_idx++;
            }
            done=left_idx<0 || right_idx==nums.size();
        }
        if (left_idx<0){
            for (int i=right_idx;i<nums.size();++i)
                result.push_back(nums[i]*nums[i]);
        }
        else{
            for (int i=left_idx;i>=0;--i)
                result.push_back(nums[i]*nums[i]);
        }
        return result;
    }
};