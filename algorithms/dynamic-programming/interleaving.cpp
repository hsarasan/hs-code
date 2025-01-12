/*
Given 3 strings s1, s2, and s3, check if s3 can be formed by an interleaving of s1 and s2.
An interleaving of two strings s and t is a configuration where they are divided into 
non-empty substrings such that:
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...

Example:
input:
s1 = "aabcc"
s2 = "dbbca"
s3 = "aadbbcbcac"
output: true
explanation:
s1 = "aabcc" = "aa" + "bc" + "c"
s2 = "dbbca" = "dbbc" + "a"
s3 = "aadbbcbcac" = "aa" + "dbbc" + "bc" + "a" + "c"
You can see that we could make s3 by taking "aa" from s1, "dbbc" from s2, 
"bc" from s1, "a" from s2, and "c" from s1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>


using namespace std;

//is t a substring of s?
bool isSubstringOf(string s, string t, string &sminust){
    int n=s.size();
    vector<int> dp(n+1,0);
    int t_idx=0;
    char search_char=t[t_idx];
    for (int i=1;i<n+1;++i){
        if (search_char==s[i-1]){
            dp[i]=dp[i-1]+1;
            search_char=t[++t_idx];
        }
        else{
            sminust.append({s[i-1]});
            dp[i]=dp[i-1];
        }
    }
    return dp[n]>=t.size();
}

bool isInterLeaving(string s1, string s2, string s3){
    if (s3.size()!=s1.size()+s2.size()) return false;
    string s3minuss1;
    bool b=isSubstringOf(s3,s1,s3minuss1); 
    if (!b) return false;
    return s3minuss1==s2;
}
int main(){
    string s1 = "aabcc";
    string s2 = "dbbca";
    string s3 = "aadbbcbcac";
    bool b=isInterLeaving(s1,s2,s3) || isInterLeaving(s2,s1,s3);
    cout<<b<<endl;
}
