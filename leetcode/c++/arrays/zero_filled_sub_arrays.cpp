/*
Given an integer array nums, return the number of subarrays filled with 0.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,3,0,0,2,0,0,4]
Output: 6
Explanation: 
There are 4 occurrences of [0] as a subarray.
There are 2 occurrences of [0,0] as a subarray.
There is no occurrence of a subarray with a size more than 2 filled with 0. Therefore, we return 6.
Example 2:

Input: nums = [0,0,0,2,0,0]
Output: 9
Explanation:
There are 5 occurrences of [0] as a subarray.
There are 3 occurrences of [0,0] as a subarray.
There is 1 occurrence of [0,0,0] as a subarray.
There is no occurrence of a subarray with a size more than 3 filled with 0. Therefore, we return 9.
Example 3:

Input: nums = [2,10,2019]
Output: 0
Explanation: There is no subarray filled with 0. Therefore, we return 0.
 

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
*/

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;
class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {

        vector<int> continuous_zero_subarray_lengths;
        int zero_count{0};
        for (int i=0; i<nums.size(); ++i){
            if (nums[i]==0){
                zero_count++;
                if (i==nums.size()-1) {
                    continuous_zero_subarray_lengths.push_back(zero_count);
                }
            }
            else{

                if (zero_count>0) {
                    continuous_zero_subarray_lengths.push_back(zero_count);
                }
                zero_count=0;
            }
        }
        long long subarray_count=0;
        for (const int z: continuous_zero_subarray_lengths){
            subarray_count = subarray_count+ (long long) z*(z+1)/2;
        }
        return subarray_count;
    }
};

int main(){
    Solution soln;
    vector<int> nums1 = {1,3,0,0,2,0,0,4};
    vector<int> nums2 = {0,0,0,2,0,0};
    vector<int> nums3 = {2,10,2019};
    assert(soln.zeroFilledSubarray(nums1)==6);
    assert(soln.zeroFilledSubarray(nums2)==9);
    assert(soln.zeroFilledSubarray(nums3)==0);
    return 0;   
}

