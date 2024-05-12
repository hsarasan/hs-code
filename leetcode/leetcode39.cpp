#include <vector>

using namespace std;

class Solution {
    std::vector<vector<int>> results;
    void backtrack(vector<int>& candidates, int start, int target, vector<int> result) {
        if (target==0){
            results.push_back(result);
            return ;
        }
        if(target<0){
            return;
        }
        for (int i=start; i<candidates.size(); ++i){
            result.push_back(candidates[i]);
            backtrack(candidates,i,target-candidates[i],result);
            result.pop_back();
        }

       
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        
        backtrack(candidates,0,target,std::vector<int>{});
        return results;

    }
};