/*
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
*/

//This is solved by Moores voting algorithm
/*
The intuition behind the Moore's Voting Algorithm is based on the fact that if there is a majority element in an array, it will always remain in the lead, even after encountering other elements.

*/

#include <vector>
#include <algorithm>

class Solution {
public:
    int majorityElement(std::vector<int>& nums) {
        int count{0};
        int candidate{nums[0]};
        auto counter= [&count,&candidate](int n){
            if (count==0)
            {
                candidate = n;
                count++;
            }
            else{
                if (n==candidate)
                {
                    count++;
                }
                else
                {
                    count--;
                }
            }

        };

        std::for_each(nums.begin(), nums.end(), counter);
        return candidate;
    }
};