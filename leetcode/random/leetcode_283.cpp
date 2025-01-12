/*
283. Move Zeroes

Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Note that you must do this in-place without making a copy of the array.
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int N=nums.size();
        int zero_count{0};
        for (int i=0; i<N; ++i){
            if (nums[i]==0) zero_count++;
            else{
                nums[i-zero_count]=nums[i];
            }
        }
        for (int i=nums.size()-zero_count;i<nums.size();++i)
            nums[i]=0;
        }
};