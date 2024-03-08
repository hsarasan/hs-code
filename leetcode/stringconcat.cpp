/*
Leetcode Problem 30. Substring with Concatenation of All Words
*/

class Solution {

    std::unordered_set<string> S;
   
    bool checkString(string s,vector<string>& words, int size){
        std::vector<string> foundWords;
        int pos=0;
        while(pos<s.size()){
            auto str = s.substr(pos,size);
            if (S.count(str)==0) return false;
            foundWords.push_back(str);
            pos=pos+size;
        }
        if ( !std::ranges::is_sorted(foundWords)) 
            std::ranges::sort(foundWords);
        return foundWords==words;
    }
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int size=words[0].size();
        std::ranges::sort(words);
        for (const auto word: words){
            S.insert(word);
        }
        vector<int> results;
        int lengthOfSubstring = words.size()*words[0].size();
        for (int i=0; i<s.size()-lengthOfSubstring+1;++i){
            std::string s1(s.begin()+i,s.begin()+i+lengthOfSubstring);
            bool b=checkString(s1,words, size);
            if(b) results.push_back(i);
        }
        return results;
    }

};