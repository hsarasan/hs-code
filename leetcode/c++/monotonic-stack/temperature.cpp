#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        int n=temperatures.size();
        vector<int> result(n,0);
        st.push(0);
        int idx;
        for (int i=1; i<n; ++i){
            int temperature=temperatures[i];
            while (!st.empty() && temperatures[st.top()]<temperature){
                idx=st.top();
                st.pop();
                result[idx]=i-idx;
            }
            st.push(i);

        }
        return result;
    }
};

int main(){
    vector<int> temperatures={73, 74, 75, 71, 69, 72, 76, 73};
    Solution sol;
    vector<int> result=sol.dailyTemperatures(temperatures);
    vector<int> expected={1, 1, 4, 2, 1, 1, 0, 0};
    assert(result==expected);
    return 0;
}