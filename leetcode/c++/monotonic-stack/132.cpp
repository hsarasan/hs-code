#include <bits/stdc++.h>
#include <cassert>

using namespace std;

class Solution {

    void printstack(stack<int> st){
        while(!st.empty()){
            cout<<st.top()<<" ";
            st.pop();
        }
        cout<<endl;
    }
public:

bool find132pattern(vector<int>& nums) {
    int n = nums.size();
    if (n < 3) return false;

    stack<int> ajcandidates;
    int ak = INT_MIN;  
    for (int i = n - 1; i >= 0; --i) {
        if (nums[i] < ak) return true; 
        while (!ajcandidates.empty() && ajcandidates.top() < nums[i]) {
            ak = ajcandidates.top();  
            ajcandidates.pop();               
        }
        ajcandidates.push(nums[i]);  
    }
    return false;  
    }
};


int main(){
    Solution s;
    vector<int> nums = {1,2,3,4};
    assert(s.find132pattern(nums) == false);
    nums = {3,1,4,2};
    assert(s.find132pattern(nums) == true);
    nums = {-1, 3, 2, 0};
    assert(s.find132pattern(nums) == true);
    nums = {1, 0, 1, -4, -3};
    assert(s.find132pattern(nums) == false); 
    return 0;   
}