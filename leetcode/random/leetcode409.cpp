class Solution {
public:
    int longestPalindrome(string s) {
        std::unordered_map<char,int> hashmap;
        for (const auto &  c: s) hashmap[c]++;
        bool isAnOddPresent{false};
        int count=0;
        for (const auto & [k,v]: hashmap){
            if (v%2==0) count+=v;
            else { count+=v-1; isAnOddPresent=true;}
        }
        return count + bool(isAnOddPresent);
    }
};