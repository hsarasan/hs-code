//338. Counting Bits
//Given an integer n, return an array ans of length n + 1 such that for
//each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.


class Solution {
    bool is_power_of_2(int i){
        bitset<32> b(i);
        return b.count()==1;
    }
public:
    vector<int> countBits(int n) {
        vector<int> dp(n+1,0);
        if (n==0) return dp;
        if (n==1){
            dp[1]=1;
            return dp;
        }
        if (n==2){
            dp[1]=1;
            dp[2]=1;
            return dp;
        }
        dp[0]=0;
        dp[1]=1;
        dp[2]=1;
        int prev_power_of_2 = 2;
        for (int i=3;i<n+1;++i){
            if (is_power_of_2(i)){
                dp[i]=1;
                prev_power_of_2=i;
            }
            else{
                dp[i]=1+dp[i-prev_power_of_2];
            }
        }
        return dp;
    }
};