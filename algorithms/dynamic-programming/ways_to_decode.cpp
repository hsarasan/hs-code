/*
A string made of letters can be encoded by replacing each letter by its position in the alphabet 
(e.g.: ELD -> 5124), but when decoding, a same encoded string can have multiple ways to be decoded 
(e.g.: 5124 can be decoded as 5 1 2 4 (EABD), or 5 12 4 (ELD), or 5 1 24 (EAX)).

Given an encoded string s made of numbers, find the number of possible ways to decode it 
by following this decoding map:

1 -> A,   2 -> B,   3 -> C,   4 -> D,   5 -> E,   6 -> F,   7 -> G,   8 -> H,   9 -> I,   10 -> J,   
11 -> K,   12 -> L,   13 -> M,   14 -> N,   15 -> O,   16 -> P,   17 -> Q,   18 -> R,   19 -> S,   
20 -> T,   21 -> U,   22 -> V,   23 -> W,   24 -> X,   25 -> Y,   26 -> Z
Example:
input:
s = "512810120129"
output: 4

explanation: There are 4 possible ways to decode s:
5   1   2   8   10   1   20   1   2   9
5   1   2   8   10   1   20   12   9
5   12   8   10   1   20   1   2   9
5   12   8   10   1   20   12   9

Constraints:
len(s) >= 1
'0' <= s[i] <= '9'
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;

vector<int> possible_combinations(vector<int> endings, int i){

    vector<int> result;
    for (const auto & end: endings){
        if (end!=0 && i!=0) result.push_back(i);
        int v=10*end + i;
        if (v>0 && v<27) result.push_back(v);
    }
    return result;
}

int no_of_combinations(string s){
    int n=s.size();
    vector<int> dp(n+1,0);
    vector<int> endings{0};
    for (int i=1;i<n+1;++i){
        int v=s[i-1]-'0';
        endings=possible_combinations(endings, v);
        dp[i]=max(dp[i-1], (int)endings.size());
    }
    return dp[n];
}

int main(){
    int n=no_of_combinations("512810120129");
    cout<<n<<endl;
    return 0;
}