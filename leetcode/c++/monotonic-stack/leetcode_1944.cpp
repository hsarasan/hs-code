#include <bits/stdc++.h>

using namespace std;


class Solution {
    public:
        vector<int> canSeePersonsCount(vector<int>& heights) {
            stack<int> st;
            int n=heights.size();
            vector<int> result(n,1);
            st.push(n-1);
            result[n-1]=0;
    
            for (int i=n-2;i>=0;--i){
                int count=0;
                while(!st.empty() && heights[st.top()]<heights[i]){
                    count++;
                    st.pop();    
                }
                result[i]=count + (st.empty()?0:1);
                st.push(i);
            }
    
            return result;
        }
    };

    int main(){
        Solution s;
        vector<int> heights = {10,6,8,5,11,9};
        vector<int> result = s.canSeePersonsCount(heights);
        assert(result == vector<int>({3,1,2,1,1,0}));
        heights={5,1,2,3,10};   
        result = s.canSeePersonsCount(heights);
        assert(result == vector<int>({4,1,1,1,0}));
        return 0;   
    }