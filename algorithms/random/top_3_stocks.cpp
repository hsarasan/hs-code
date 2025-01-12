#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

int N=3;
using namespace std;
struct Compare{
    bool operator()(const pair<int,string> &p1 , const pair<int,string> &p2) {
        return p1.first>p2.first;
    }
};
using T1=pair<int,string>;
priority_queue<T1,vector<T1>,Compare> PQ;
unordered_map<string,int> stocks_counter;

void deleteEntryFromPQ(string stock){
    priority_queue<T1, vector<T1>, Compare> PQ_copy;
    while (PQ.size()!=0){
        auto p=PQ.top();
        if (PQ.top().second!=stock) PQ_copy.push(p);
        PQ.pop();
    }
    PQ.swap(PQ_copy);
}

void submit(const string & stock, int number){
    stocks_counter[stock]+=number;
    deleteEntryFromPQ(stock);
    PQ.push({stocks_counter[stock], stock});
    while (PQ.size()>N) PQ.pop();
}
void print(){
    auto PQ_copy = PQ;
    while(PQ_copy.size()!=0){
        auto p = PQ_copy.top();
        PQ_copy.pop();
        std::cout<<p.second<<"=>"<<p.first<<std::endl;   
           
    }
    std::cout<<"================="<<std::endl; 
}


int main(){
    submit("MSFT",10);
    submit("GOOGLE",200);
    submit("BBG",30);
    print();

    submit("AAPL",100);
    submit("IBM",150);
    submit("GOOGLE",200);
    print();

    submit("GOOGLE",1200);
    submit("MSFT",1000);
    print();
}