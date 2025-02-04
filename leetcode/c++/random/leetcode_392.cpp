/*
392. Is Subsequence
Given two strings s and t, return true if s is a subsequence of t, or false otherwise.
A subsequence of a string is a new string that is formed from the original string by deleting 
some (can be none) of the characters without disturbing the relative positions of the remaining 
characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).*/
#include <iostream>
#include <string>

using namespace std;

class Solution {
    int getPositionOfCharacter(string s, size_t start_position, char c){
        return s.find(c,start_position);
    }
public:
    bool isSubsequence(string s, string t) {
        size_t start=0;
        for (const char c: s){
            size_t pos;
            pos=getPositionOfCharacter(t,start,c);
            if (pos==string::npos) 
            {
                return false;
            }
            start=pos+1;
        }
        return true;
    }
};

int main(){
    
}