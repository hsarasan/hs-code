#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <type_traits>
#include <algorithm>
#include <iterator>

template <typename T>
struct is_containerlog_supported: std::false_type {};

template <typename T>
struct is_containerlog_supported<std::vector<T>>: std::true_type{};

template <typename T>
struct is_built_in_type: std::false_type{};

template <>
struct is_built_in_type<int>: std::true_type{};


template <typename Iterator>
void print(const Iterator first, const Iterator last)
{
    auto iter = first;
    while (iter!=last)
    {
        std::cout<<*iter++<<" ";
    }
    std::cout<<std::endl;
}


template<typename T, typename std::enable_if_t<is_containerlog_supported<T>::value, T> * = nullptr>
void log(T &v)
{
    print(v.begin(), v.end());
}

template <typename T=std::string, typename T2=void*>
void log(std::string &v)
{
    std::cout<<"S'"<<v<<std::endl;
}

template <typename T, 
typename std::enable_if_t<!is_containerlog_supported<T>::value, T> * = nullptr,
typename std::enable_if_t<!is_built_in_type<T>::value, T> * = nullptr>
void log(T &v)
{
    std::cout<<"Implementation not supported "<<std::endl;
}


template<typename T,  typename std::enable_if_t<is_built_in_type<T>::value, T> * = nullptr>
void log(const T& x) {
    std::cout<<"R"<<std::to_string(x);
}



int main(){

    std::vector<int> v{1,2,3};
    log(v);
    log(v[0]);
    std::set<int> s{1,2,3};
    log(s);
    std::string x("abc");
    log(x);
    return 0;
}