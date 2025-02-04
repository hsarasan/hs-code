/*
Given an integer array nums, return true if there exists a triple of indices (i, j, k) such that i < j < k and nums[i] < nums[j] < nums[k]. 
If no such indices exists, return false.

Example 1:
Input: nums = [1,2,3,4,5]
Output: true
Explanation: Any triplet where i < j < k is valid.
Example 2:

Input: nums = [5,4,3,2,1]
Output: false
Explanation: No triplet exists.
Example 3:

Input: nums = [2,1,5,0,4,6]
Output: true
Explanation: The triplet (3, 4, 5) is valid because nums[3] == 0 < nums[4] == 4 < nums[5] == 6.
 
Constraints:

1 <= nums.length <= 5 * 105
-231 <= nums[i] <= 231 - 1
 
Follow up: Could you implement a solution that runs in O(n) time complexity and O(1) space complexity?
*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    bool increasingTriplet(const vector<int>& nums) {
        int l1{nums[0]};
        int l2{INT_MAX};
        int candidate_l1{INT_MAX};
        int candidate_l1_exists{false};
        bool found_l2{false};
        for (int i=1; i<nums.size(); ++i){
            //cout<<"Processing "<<nums[i]<<endl;
            //cout<<"l1="<<l1<<" l2="<<l2<<" candidate_L1="<<candidate_l1<<" candidaet_l1_exists="<<candidate_l1_exists<<endl;
            if (!found_l2){
                if (nums[i]>l1) {
                    //cout<<"AA setting l2 to "<<nums[i]<<" while l1 is "<<l1<<endl;
                    l2=nums[i];
                    found_l2=true;
                }
                else if (nums[i]<l1){
                    //cout<<"BB Setting l1 to "<<nums[i]<<endl;
                    l1=nums[i];
                }
            }
            else {
                
                if (nums[i]>l2) {
                    //cout<<l1<<" "<<l2<< " "<<nums[i]<<endl;
                    return true;
                }

                if (candidate_l1_exists && nums[i]<candidate_l1){
                    candidate_l1=nums[i];
                }
                else if (nums[i]<l1) {
                    if (candidate_l1_exists){
                        //cout<<"CC Setting l1 l2 to "<<candidate_l1<<" "<<nums[i]<<endl;
                        l1=candidate_l1;
                        l2=nums[i];
                    }
                    else{
                        candidate_l1=nums[i];
                        candidate_l1_exists=true;
                    }
                }
                else if(nums[i]>l1) {
                    if (candidate_l1_exists){
                        //cout<<"EE setting l1 to "<<candidate_l1<<" l2 t "<<min(l2,nums[i]);
                        l1=candidate_l1;
                        l2=min(l2,nums[i]);
                        candidate_l1_exists=false;
                    }
                    else {
                        //cout<<"EE setting l2 to "<<min(l2,nums[i])<<" while l1 stays at "<<l1<<endl;
                        l2=min(l2,nums[i]);
                    }
                    
                }
                else if (nums[i]==l1){
                    if (candidate_l1_exists){
                        l1 = candidate_l1;
                        l2 = nums[i];
                        candidate_l1_exists=false;
                    }
                }

            }
        }
        return false;

    }
};

int main(){
    Solution s;
    assert(s.increasingTriplet(vector<int>{1,2,3,4,5})==true);
    assert(s.increasingTriplet(vector<int>{5,4,3,2,1})==false);
    assert(s.increasingTriplet(vector<int>{2,1,5,0,4,6})==true);
    assert(s.increasingTriplet(vector<int>{1,2,3,1,2,1})==true);
    return 0;
}