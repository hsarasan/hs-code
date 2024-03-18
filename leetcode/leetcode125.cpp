/*

125. Valid Palindrome

A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.
*/


class Solution {
public:
    bool isPalindrome(string s) {
        auto fwd=s.begin();
        auto rev=s.rbegin();
        bool done=false;
        while(!done){
        while(fwd!=s.end() && isalnum(*fwd)==false ){fwd++;}
        while(rev!=s.rend() && isalnum(*rev)==false ){rev++;}
        if (fwd==s.end()|| rev==s.rend()) return true;
        if (fwd!=s.end() && rev!=s.rend()){
            if (fwd<rev.base()){
                auto f=*fwd;
                auto r=*rev;
                std::cout<<f<<","<<r<<std::endl;
                if(std::tolower(f)!=std::tolower(r)){
                
                    return false;
                }
            }
        }
            
            fwd++;
            rev++;
            done=fwd>rev.base();
        }
        return true;
    }
};