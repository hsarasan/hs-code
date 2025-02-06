#include <bits/stdc++.h>

using namespace std;

class StockSpanner {
    vector<int> prices;
    stack<int> st;
public:
    StockSpanner() {
        prices=vector<int>();

    }
    
    int next(int price) {
        prices.push_back(price);
        int n=prices.size();
        if (st.empty()) {
            st.push(n-1);
            return 1;
        }
        while(!st.empty() && price>=prices[st.top()]){
            st.pop();
        } 
        
        if (st.empty()) {
            st.push(n-1);
            return n;
        }
        int prev=st.top();
        st.push(n-1);
        return n-1-prev;

    }
};

int main(){
    StockSpanner spanner;
    vector<int> prices={100, 80, 60, 70, 60, 75, 85};
    vector<int> expected={1, 1, 1, 2, 1, 4, 6};
    for (int i=0; i<prices.size(); ++i){
        assert(spanner.next(prices[i])==expected[i]);
    }
    return 0;
}