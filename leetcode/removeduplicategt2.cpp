/*
Given an integer array nums sorted in non-decreasing order, remove some duplicates in-place such that each unique element appears at most twice. The relative order of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the first part of the array nums. More formally, if there are k elements after removing the duplicates, then the first k elements of nums should hold the final result. It does not matter what you leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        auto pos_iter=nums.begin()+1;
        auto iter = nums.begin()+2;
        bool pos_occured_twice=(*(pos_iter-1)==*pos_iter);
        while (iter<nums.end())
        {
            if (*iter==*pos_iter)
            {
                if (!pos_occured_twice)
                {
                    pos_occured_twice=true;
                    pos_iter++;
                    *pos_iter = *iter;
                }
            }
            else
            {
                pos_occured_twice=false;
                pos_iter++;
                *pos_iter = *iter;
            }
            iter++;
        }
        return std::distance(nums.begin(), pos_iter)+1;
    }
};