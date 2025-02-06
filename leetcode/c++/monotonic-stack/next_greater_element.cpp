#include <vector>
#include <unordered_map>
#include <iostream>
#include <stack>
#include <cassert>

using namespace std;


class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int,int> hashmap;
        stack<int> st;
        int m=nums1.size();
        int n=nums2.size();
        st.push(0);
        for (int i=1; i<n; ++i){
            int num=nums2[i];
            while(!st.empty() && num>nums2[st.top()]){
                hashmap[nums2[st.top()]]=num;
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty()){
            hashmap[nums2[st.top()]]=-1;
            st.pop();
        }
        //for (const auto &[k,v]: hashmap){
        //    cout<<k<<"=>"<<v<<" ";
        //}
        cout<<endl;
        vector<int> result(m,-1);
        for (int i=0; i<m; ++i){
            result[i]=hashmap[nums1[i]];
        }
        return result;
    }
};


int main(){
    vector<int> nums1={4,1,2};
    vector<int> nums2={1,3,4,2};
    Solution sol;
    vector<int> result=sol.nextGreaterElement(nums1,nums2);
    vector<int> expected={-1,3,-1};
    assert(result==expected);
    nums1={2,4};
    nums2={1,2,3,4};
    result=sol.nextGreaterElement(nums1,nums2);
    expected={3,-1};
    assert(result==expected);
    return 0;
}   


