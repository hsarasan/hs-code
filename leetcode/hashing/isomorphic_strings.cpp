
/*
Isomorphic Strings Given two strings s and t, determine if they are isomorphic. 
Two strings s and t are isomorphic if the characters in s can be replaced to get t. All occurrences of a character must be replaced with another character while preserving the order of characters. 
No two characters may map to the same character, but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"

Output: true

Explanation:

The strings s and t can be made identical by:

Mapping 'e' to 'a'.
Mapping 'g' to 'd'.
Example 2:

Input: s = "foo", t = "bar"

Output: false

Explanation:

The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:

Input: s = "paper", t = "title"

Output: true
*/
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <string>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char,char> char_map;
        unordered_map<char,char> reverse_char_map;
        if (s.size()!=t.size()) return false;
        size_t n=s.size();
        for (int i=0; i<n; ++i){
            char c1=s[i];
            char c2=t[i];
            if (char_map.count(c1)==0){
                if (reverse_char_map.count(c2)!=0) return false;
                char_map[c1]=c2;
                reverse_char_map[c2]=c1;
            }
            else{
                if (char_map[c1]!=c2) return false;
            }
        }
        return true;
    }
};

int main(){
    Solution s;
    string s1 = "egg";
    string t1 = "add";
    assert(s.isIsomorphic(s1,t1)==true);
    string s2 = "foo";
    string t2 = "bar";
    assert(s.isIsomorphic(s2,t2)==false);
    string s3 = "paper";
    string t3 = "title";
    assert(s.isIsomorphic(s3,t3)==true);
    return 0;       
}