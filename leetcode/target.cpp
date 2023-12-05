/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

*/
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>


class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::map<int, int> m;
        int n = nums.size();
        for (int i=0; i<n; ++i)
        {
            m.insert( {nums[i],i});
        }
        for (int i=0;i<n; ++i)
        {
            int compliment = target - nums[i];
            std::cout<<"Looking for "<<compliment <<" in ";
            for(const auto& [k,v]:m)
            {
                std::cout<<k<<","<<v<<"||";
            }
            std::cout<<std::endl;
            auto iter = m.find(compliment);
            if ( (iter!=m.end() && (i!=iter->second)) )
            {
                std::cout<<i<<" "<<iter->second<<std::endl;
                return std::vector<int>{i,iter->second};
            }
        }
        return std::vector<int>{};
    }
};

int main() {

    Solution s;
    /*
    {
    std::vector<int> v{7,12,2,4,5};
    auto a = s.twoSum(v,9);
    std::for_each(std::begin(a),std::end(a),[](int & x){ std::cout<<x<<" ";});
    std::cout<<" ["<<a.size()<<"]"<<std::endl;
    }
    {
    std::vector<int> v{7,12,24,5};
    auto a = s.twoSum(v,9);
    std::for_each(std::begin(a),std::end(a),[](int & x){ std::cout<<x<<" ";});
    std::cout<<" ["<<a.size()<<"]"<<std::endl;
    }
    */
    {
    std::vector<int> v{3,2,4};
    auto a = s.twoSum(v,6);
    std::for_each(std::begin(a),std::end(a),[](int & x){ std::cout<<x<<" ";});
    std::cout<<" ["<<a.size()<<"]"<<std::endl;
    }
}