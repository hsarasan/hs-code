class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int insert_position=0;

        for (int i=0;i<nums.size();++i){
            if (nums[i]!=0 ) {
                nums[insert_position++]=nums[i];
            }
        }
        for (int i=insert_position; i<nums.size(); ++i){
            nums[i]=0;
        }
    }
};
