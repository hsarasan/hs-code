#include <bits/stdc++.h>

using namespace std;

template <int N>
struct TopCounter{
    unordered_map<string,int> current_top_stocks;
    int min_count_to_qualify{0};

    void eraseMin(){
        
        auto iter=find_if(current_top_stocks.begin(), current_top_stocks.end(), [&](const pair<string,int> &p){
                return p.second==min_count_to_qualify;
            });
        cout<<"Need to erase "<<iter->first<<endl;
        current_top_stocks.erase(iter);
        
    }
    int getMin(){
        int minv=INT_MAX;
        for (const auto &[k,v]: current_top_stocks)
            minv=min(minv,v);
        return minv;
    }

    void add(string stock, int count){
        if (current_top_stocks.count(stock)!=0){
            current_top_stocks[stock]=count;
            min_count_to_qualify=getMin();
            return;
        }
        if (min_count_to_qualify>count && current_top_stocks.size()==N) return;
        if (current_top_stocks.size()==N) eraseMin();
        current_top_stocks[stock]=count;
        min_count_to_qualify=getMin();
    }
    void print(){
        
        for (const auto & [k,v]: current_top_stocks){
            cout<<k<<"-"<<v<<" ";
        }
        cout<<endl;
    }
    
};

int main(){

    TopCounter<3> TopStocks;
    TopStocks.add("AAPL",1000);
    TopStocks.print();
    TopStocks.add("AAPL",2000);
    TopStocks.print();
    TopStocks.add("GOOGLE",2000);
    TopStocks.print();
    TopStocks.add("IBM",300);
    TopStocks.print();   
    TopStocks.add("GOOGLE",4000);
    TopStocks.print(); 
    TopStocks.add("MSFT",1000);
    TopStocks.print();
    TopStocks.add("FB",1000);
    TopStocks.print();
    TopStocks.add("BP",500);
    TopStocks.print();
    TopStocks.add("IBM",30000);
    TopStocks.print();
}


