#include <bits/stdc++.h>


using namespace std;
class Solution {
    public:
        int largestRectangleArea(vector<int>& heights) {
                stack<int> st;
        int maxArea = 0;
        int n = heights.size();
    
        for (int i = 0; i <= n; i++) {
            while (!st.empty() && (i == n || heights[st.top()] > heights[i])) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width); 
            }
            st.push(i);
        }
    
        return maxArea;
        }
    };

    int main(){
        Solution s;
        vector<int> heights = {2,1,5,6,2,3};
        assert(s.largestRectangleArea(heights) == 10);
        heights = {2,4};
        assert(s.largestRectangleArea(heights) == 4);
        heights = {2,1,2};
        assert(s.largestRectangleArea(heights) == 3);
        return 0;
    }