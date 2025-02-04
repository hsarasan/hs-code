class Solution {
    void print(const vector<int> & nums){
        std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ","));
        std::cout<<std::endl;
    }
    vector<vector<int>> fillCombinations(vector<int> nums){
        vector<vector<int>> results;
        if (nums.size()<2) {
            results.push_back({nums});
            return results;
        };
        
        for (int i=0;i<nums.size();++i){
            auto value=nums[i];
            auto nums_copy = nums;
            nums_copy.erase(nums_copy.begin()+i);
            auto results_i = fillCombinations(nums_copy);
            for (auto & result: results_i){
                result.push_back(value);
                results.push_back(result);
            }

        }
        return results;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return fillCombinations(nums);
 

    }
};