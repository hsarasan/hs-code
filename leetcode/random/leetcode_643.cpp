/*
643. Maximum Average Subarray I
You are given an integer array nums consisting of n elements, and an integer k.
Find a contiguous subarray whose length is equal to k that has the maximum average 
value and return this value. Any answer with a calculation error less than 10-5 will be accepted.
*/

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int N=nums.size();
        vector<int> Sums(N+1,0);
        for (int i=0; i<N; ++i){
            Sums[i+1]=Sums[i]+nums[i];
        }
        int k_total=INT_MIN;
        for (int i=N;i>=k; --i){
            k_total=max(k_total,Sums[i]-Sums[i-k]);
        }
        return (double)k_total/k;
        
    }
};