/*
Given a string text, you want to use the characters of text to form as
 many instances of the word "balloon" as possible.

You can use each character in text at most once. 
Return the maximum number of instances that can be formed*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char,int> hash_map;
        for (char c: string("balloon") ){
            hash_map[c]++;
        }
        unordered_map<char,int> text_map;
        for (char c: text){
            if (hash_map.count(c)>0){
                text_map[c]++;
            }
        }
        if (hash_map.size()!=text_map.size()) return 0;
        int min_count=INT_MAX;
        for (const auto & [k,v]: text_map){
            min_count=min(min_count,v/hash_map[k]);
        }
        return min_count;
    }
};

int main(){
    Solution s;
    string text="nlaebolko";
    assert(s.maxNumberOfBalloons(text)==1);
    text="loonbalxballpoon";
    assert(s.maxNumberOfBalloons(text)==2);
    text="leetcode";
    assert(s.maxNumberOfBalloons(text)==0);
    return 0;
}       