/*
844. Backspace String Compare

Given two strings s and t, return true if they are equal when both are typed into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

*/
class Solution {
    vector<char> string_to_vector(const string &s){
        vector<char> v;
        for (char c: s){
            if (c=='#') {
                if (v.size()>0)
                    v.pop_back();
            } 
            else{
                v.push_back(c);
            }
        }
        return v;
    }
public:
    bool backspaceCompare(string s, string t) {
        vector<char> sv = string_to_vector(s);
        vector<char> tv = string_to_vector(t);
        return sv==tv;
    }
};