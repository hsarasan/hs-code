/*
169. Majority Element
Given an array nums of size n, return the majority element.
The majority element is the element that appears more than ⌊n / 2⌋ times. 
You may assume that the majority element always exists in the array.
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int leader;
        int leader_count=0;
        for (const int num: nums){
            if (leader_count==0){
                leader=num;
                leader_count=1;
            }
            else if (num==leader){
                leader_count++;
            }
            else{
                leader_count--;
            }
        }
        return leader;
    }
};