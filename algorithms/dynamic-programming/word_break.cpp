/*
Given a string s and a list of words, check if we can break s into words from the list
 (A same word can be used multiple times).

Example:

input:
s = "catsandogsareanimals"
words = ["cats", "dog", "sand", "and", "cat", "mals", "san", "dogs", "are", "animal", "ani", "og", "sar"]
output: true
explanation: s is also equal to "cat"+"san"+"dogs"+"are"+"ani"+"mals", and all of these parts are in words
Constraints:

len(s) >= 1
len(words) >= 1
len(words[i]) >= 1
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool isMatch(const unordered_set<string> dict, string s){
    int n=s.size();
    vector<int> dp(n+1,0);
    string traversing;
    for (int i=1;i<n+1;++i){
        traversing=traversing+s[i-1];
        if (dict.count(traversing)>0){
            dp[i]=1;
        }
        else{
            for (int j=0;j<i;++j){
                if (dp[j]==1){
                    string ss=traversing.substr(j-1,i-j);
                    if (dict.count(ss)==1){
                        dp[i]=1;
                    }
                        
                }
            }
        }
    }

    return dp[n];
}

int main(){
    unordered_set<string> dict = {"cats", "dog", "sand", "and", "cat", "mals", "san", "dogs", "are", "animal", "ani", "og", "sar"};
    bool b = isMatch(dict,"catsandogsareanimals");
    cout<<b<<endl;
    b = isMatch(dict,"catsandogsareanimales");
    cout<<b<<endl;
    return 0;
}
