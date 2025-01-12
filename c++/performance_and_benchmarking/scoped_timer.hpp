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
