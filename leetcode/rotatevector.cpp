/* Rotate a vector by 3*/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {

public:
    void rotate(std::vector<int>& nums, int k) {

        auto n=nums.size();
        if (k>n) k=k%n;
        std::reverse(nums.begin(), nums.begin()+n-k);
        std::reverse(nums.begin()+n-k, nums.end());
        std::reverse(nums.begin(), nums.end()); 
    }
};