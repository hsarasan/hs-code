#include <bits/stdc++.h>

using namespace std;

class Solution {
    public:
        string removeDuplicateLetters(string s) {
            unordered_map<char,int> freq;
            unordered_map<char,bool> visited;
            stack<char> st;
            for (char c:s ) freq[c]++;
            for (char c: s){
                freq[c]--;
                if (visited[c]) continue;
                while(!st.empty() && st.top()>c && freq[st.top()]>0){
                    visited[st.top()]=false;
                    st.pop();
                }
                visited[c]=true;
                st.push(c);
            }
            string result;
            while(!st.empty()){
                result=result+st.top();
                st.pop();
            }
            reverse(result.begin(),result.end());
            return result;
        }
    };

    int main() {
        Solution s;
        string str = "bcabc";
        assert(s.removeDuplicateLetters(str) == "abc");
        str = "cbacdcbc";   
        assert(s.removeDuplicateLetters(str) == "acdb");
        return 0;
    }