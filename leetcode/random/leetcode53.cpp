class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int globalMax=nums[0];
        int subMax = nums[0];
        for (int i=1;i<nums.size();++i){
            subMax=std::max(subMax+nums[i],nums[i]);
            globalMax=std::max(globalMax,subMax);
        }
        return globalMax;
    }
};