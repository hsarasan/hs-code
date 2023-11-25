/*
Given an integer array nums and an integer val, remove all occurrences of val in nums in-place. The order of the elements may be changed. Then return the number of elements in nums which are not equal to val.

Consider the number of elements in nums which are not equal to val be k, to get accepted, you need to do the following things:

Change the array nums such that the first k elements of nums contain the elements which are not equal to val. The remaining elements of nums are not important as well as the size of nums.
Return k.
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int removeElement(std::vector<int>& nums, int val) {
        auto fwd_iter = std::find(nums.begin(), nums.end(), val);
        auto comp = [&](int n){ return n!=val; };
        auto rev_iter = std::find_if(nums.rbegin(), nums.rend(), comp);
        while (fwd_iter<rev_iter.base())
        {
            std::swap(*fwd_iter,*rev_iter);
            fwd_iter = std::find(++fwd_iter, nums.end(), val);
            rev_iter = std::find_if(++rev_iter, nums.rend(), comp);
        }
        return std::distance(nums.begin(), fwd_iter );
    }
};

int main(){
    
}
