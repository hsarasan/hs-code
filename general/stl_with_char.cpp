#include <iostream>
#include <algorithm>
#include <cstring>

int main(){
    char * test_string = new char[100];
    strcpy(test_string, "this is a test string");

    //convert first character of every word to capital
    auto iter=test_string;
    auto test_string_end = test_string+std::strlen(test_string);
    while (iter!=test_string_end){
        *iter=std::toupper(*iter);
        iter=std::find(iter,test_string_end,' ');
        if (iter!=test_string_end)
        {
            iter++;
            
        }
    }
    std::cout<<test_string<<std::endl;
}