/*
A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
 Example 1: Input: s = "abc", t = "ahbgdc" Output: true
Example 2: Input: s = "axc", t = "ahbgdc" Output: false
*/

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int t_idx = 0;
        for (int i=0;i<s.size();++i){
            char c = s[i];
            while (t_idx!=t.size() && t[t_idx]!=c) t_idx++;
            if (t_idx==t.size()) return false;
            t_idx++;
        }
        return true;
    }
};


int main(){
    Solution s;
    assert(s.isSubsequence("abc", "ahbgdc")==true);
    assert(s.isSubsequence("axc", "ahbgdc")==false);
    return 0;
}