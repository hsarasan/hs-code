/*1189. Maximum Number of Balloons Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible. 
You can use each character in text at most once. Return the maximum number of instances that can be formed.*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>


using namespace std;

class Solution {
public:
    int numIdenticalPairs(vector<int>& nums) {
        unordered_map<int,int> num_count;
        for (const auto num: nums) num_count[num]++;
        int count=0;
        for (const auto & [k,v]: num_count){
            if (v>1){
                count=count+v*(v-1)/2;
            }
        }
        return count;
    }
};

int main(){
    Solution s;
    vector<int> nums = {1,2,3,1,1,3};
    assert(s.numIdenticalPairs(nums)==4);   
    nums = {1,1,1,1};
    assert(s.numIdenticalPairs(nums)==6);
    nums = {1,2,3};
    assert(s.numIdenticalPairs(nums)==0);
    
    return 0;
}