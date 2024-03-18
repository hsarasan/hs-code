/*
Valid Anagram
Solved
Easy
Topics
Companies
Given two strings s and t, return true if t is an anagram of s, and false otherwise.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.*/
class Solution {
public:
    bool isAnagram(string s, string t) {
        std::unordered_map<char,int> hashmap_s;
        std::unordered_map<char,int> hashmap_t;
        for ( const auto ch: s) hashmap_s[ch]++;
        for ( const auto ch: t) hashmap_t[ch]++;
        return hashmap_s==hashmap_t;
    }
};