#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
#include <chrono>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <functional>

struct MyFunctor{
    int state{0};
    int operator()(int i, int j){
        state=state+i+j;
        return state;
    }
};
int add(int a , int b) { return a+b;}
int calculator(std::function<int(int,int)> callable,int i, int j){
    return callable(i,j);
}

int main(){
    auto mult=[](int a,int b){return a*b;};
    auto a = calculator(mult,5,6);
    auto b = calculator(add, 5,9);
    MyFunctor func;
    auto c = calculator(func,5,12);
    auto d = calculator(func,9,10);
    std::cout<<a<<","<<b<<","<<c<<","<<d<<std::endl;
    auto fun_2 = std::bind(add,1,std::placeholders::_1);
    auto e = fun_2(10);
    std::cout<<e<<std::endl;
    auto fun_3 = std::bind(calculator,std::placeholders::_1,10,std::placeholders::_2);
    auto f = fun_3(func,20);
    std::cout<<f<<std::endl;
}