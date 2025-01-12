class Solution {
public:
    int majorityElement(vector<int>& nums) {

        int count=0; 
        int candidate=nums[0];
        for (const auto & num : nums){
            if (count==0){
                count++;
                candidate=num;
            }
            else{
                if (candidate==num) {
                    count++;
                }
                else {
                    count--;
                }

            }
        }
        return candidate;
    }
};