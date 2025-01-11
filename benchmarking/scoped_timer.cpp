#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>

class scoped_timer
{
private:    
    const std::chrono::steady_clock::time_point start;
    const std::string identifier;
public:
    scoped_timer(const std::string & identifier_) : 
        start{std::chrono::steady_clock::now()},identifier{identifier_}{}
    ~scoped_timer(){ std::cout<<"Time taken by "<<identifier<<" is "
        <<std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - start).count()<<" ms"<<std::endl;
    }
    scoped_timer(const scoped_timer&) = delete;
    scoped_timer &operator=(const scoped_timer&) = delete;
};  

template <typename Container>
void fill_and_add(Container v){
    scoped_timer timer(__func__);
    for (int i=0; i<1000; ++i){
        std::iota(v.begin(), v.end(), 0);
        auto sum=std::accumulate(v.begin(), v.end(), 0);     
    }
}
int main(){
    fill_and_add(std::vector<int>(100000));
    fill_and_add(std::array<int,100000>());
    return 0;
}
