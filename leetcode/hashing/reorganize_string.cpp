/*
767. Reorganize string

Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.
Example 1:

Input: s = "aab"
Output: "aba"
Example 2:

Input: s = "aaab"
Output: ""
 

Constraints:

1 <= s.length <= 500
s consists of lowercase English letters.
*/

#include <bits/stdc++.h>

using namespace std;
class Solution {
    size_t getNextEmpty(string s){
        return s.find_first_of(' ');
    }
public:
    string reorganizeString(string s) {
        int n=s.size();
        unordered_map<char, int> char_map;
        map<int,set<char>, std::greater<int> > super_map; 
        for (const char c: s) char_map[c]++;
        for (const auto & [k,v]: char_map){
            super_map[v].insert(k);
        }   
        string result(n,' ');
        if (super_map.begin()->first > 1+(n-1)/2 )
            return "";
        int next = 0;
        for (const auto &[k,v]: super_map){
            for (const auto & elem: v){
                for (int j=0; j<k; ++j){
                    result[next]=elem;
                    next=next+2;
                    if (next>=n){
                        next=getNextEmpty(result);                        
                    }
                }
            }
        }
                
        return result;
    }
};

int main(){
    Solution s;
    string str="aab";
    assert(s.reorganizeString(str)=="aba");
    str="aaab";
    assert(s.reorganizeString(str)=="");
    str="aaabbb";
    assert(s.reorganizeString(str)=="ababab");

    return 0;
}