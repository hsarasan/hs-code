class Solution {
    std::string getlcp(std::string &s1, std::string &s2){
        std::string result;
        int mx=std::min(s1.length(), s2.length());
        for(int i=0;i<mx;++i){
            if (s1[i]==s2[i]) 
            {
                result+=s1[i];
            }
            else {
                return result;
            }
        }
        return result;
    }
public:
    string longestCommonPrefix(vector<string>& strs) {
        std::string result;
        if (strs.size()<2) return strs[0];
        std::sort(strs.begin(), strs.end());
        result=getlcp(strs[0],strs[strs.size()-1]);
        return result;
    }
};