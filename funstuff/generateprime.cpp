//A simple program to print all primes till N

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <map>
#include <condition_variable>

int N=20;

bool getNextPrimeAfterM(std::map<int,bool> & primeMap, int &n, int m){
    if (m>=N) return true;
    auto iter = primeMap.begin() ;
    std::advance(iter,m-1);
    for (iter; iter!=primeMap.end(); ++iter){
        if (!iter->second){
            n=iter->first;
            return false;
        }  
    }
    return true;
}

void iterateTillEnd(std::map<int,bool> & primeMap, int n){
    int k=n*2;
    while(k<N){
        primeMap[k]=true;
        k=k+n;
    }
}
void printAllPrimesTill(int N){
    std::map<int,bool> primeMap;
    primeMap[1]=true;
    for (int i=2; i<N; ++i) primeMap[i]=false;
    bool done{false};
    int n;
    int m=1;
    while(!done) {
        done=getNextPrimeAfterM(primeMap,n,m);
        if(!done){
            std::cout<<"Next Prime "<<n<<std::endl;
            iterateTillEnd(primeMap,n);
        }
        m=n+1;
    }
}


int main() {
    printAllPrimesTill(N);
    return 0;
}