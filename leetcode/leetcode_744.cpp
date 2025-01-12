/*
744. Find Smallest Letter Greater Than Target
You are given an array of characters letters that is sorted in non-decreasing order, 
and a character target. There are at least two different characters in letters.

Return the smallest character in letters that is lexicographically greater than target.
 If such a character does not exist, return the first character in letters.
*/

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        auto iter = std::upper_bound(letters.begin(), letters.end(), target);
        if (iter!=letters.end()) return *iter;
        return letters[0];
    }
};