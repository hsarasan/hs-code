#include <bits/stdc++.h>

using namespace std;

struct compare{
    bool operator()(const string &s1, const string &s2) const{
        string c1;
        string c2;
        transform(s1.begin(), s1.end(), back_inserter(c1), ::toupper);
        transform(s2.begin(), s2.end(), back_inserter(c2), ::toupper);
        return c1<c2;
    }
};

int main(){
    const set<string,compare> S{"abc","ABC","def"};
    copy(S.begin(), S.end(), ostream_iterator<string>(cout,","));
    cout<<endl;
    return 0;
}