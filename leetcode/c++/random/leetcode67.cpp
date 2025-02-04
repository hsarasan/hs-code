class Solution {
    std::tuple<char,char> getSum(char a, char b, char c){
        std::unordered_multiset<char> S({a,b,c});
        if (S.count('1')==0) return {'0','0'};
        if (S.count('1')==1) return {'0','1'};
        if (S.count('1')==2) return {'1','0'};
        return {'1','1'};

    }
public:
    string addBinary(string a, string b) {
        
        size_t a_len = a.length();
        size_t b_len = b.length();
        if (a_len>b_len){
            auto n = a_len-b_len;
            auto pad = std::string(n,'0');
            b=pad+b;
        }
        else if (a_len<b_len){
            auto n = b_len-a_len;
            auto pad = std::string(n,'0');
            a=pad+a;
        }
        char offset='0';
        int size=a.length();
        std::string result(size,'0');
        for (int i=size-1; i>=0; --i){
            auto [carry,bit]=getSum(a[i],b[i],offset);
            result[i]=bit;
            offset=carry;
        }
        if (offset=='1') return "1"+result;
        return result;
    }
};