#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;


class Solution {
public:
    string convert(string s, int numRows) {

        size_t next=0;
        auto get_next=[&]{ 
            return next>=s.size()?' ':s[next++];
        };
        vector<string> strs(numRows);
        bool done{false};
        while(!done) {
            for (int i=0; i<numRows; i++){
                char c = get_next();
                if (c==' ')
                {
                    done=true;
                    break;
                }
                strs[i]+=c;
            }
            if (done) break;
            for (int i=numRows-2; i>0; i--){
                char c = get_next();
                if (c==' '){
                    done=true;
                    break;
                }
                strs[i]+=c;
            }            
        }
        string result;
        for (const auto & str: strs){
            result=result+str;
        }
        return result;
    }
};


int main() {
    Solution sol;
    
    string s{"PAYPALISHIRING"};
    int numRows{3};
    string result = sol.convert(s, numRows);
    cout << "Result: " << result << endl;
    assert(result=="PAHNAPLSIIGYIR");
    
    s="PAYPALISHIRING";
    numRows=4;
    result = sol.convert(s, numRows);
    cout << "Result: " << result << endl;
    assert(result=="PINALSIGYAHRPI");

    s="A";
    numRows=1;
    result = sol.convert(s, numRows);
    cout << "Result: " << result << endl;
    assert(result=="A");

    return 0;
}