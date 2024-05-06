#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

class TopStocks{
    std::multimap<int, std::string> count_to_ticker;
    public:
        void printTopNStocks(int N){
            auto it = count_to_ticker.rbegin();
            for (int i=0;i<N;++i){
                std::cout<<it->second<<"=>"<<it->first<<",";
                it++;
            }
            std::cout<<std::endl;
        }
        void updateCount(const std::string & ticker, int count ){
  
            auto it = std::find_if(count_to_ticker.begin(), count_to_ticker.end(), 
                    [&](std::pair<int, std::string> p){
                        return p.second==ticker;
                    }
            );
            int new_count{count};
            if (it!=count_to_ticker.end()){
                new_count=count+it->first;
                count_to_ticker.erase(it);
            }
            count_to_ticker.insert({new_count, ticker});
        }
};

int main(){
    TopStocks ts;
    ts.updateCount("AAPL",10000);
    ts.updateCount("MSFT",2000);
    ts.updateCount("ABC",1000);
    ts.updateCount("MSFT",20000);
    ts.updateCount("AAPL",3000);
    ts.printTopNStocks(2);
    ts.updateCount("ABC",20000);
    ts.printTopNStocks(2);
    ts.updateCount("IBM",50000);
    ts.updateCount("AAPL",10000);
    ts.printTopNStocks(2);
}