#include <iostream>
#include <sstream>
#include <string>

int main(){
    std::cout<<"Enter input in <string>,<value> format "<<std::endl;
    std::string line;
    while(std::getline(std::cin,line)){
        
        std::istringstream iss(line);
        std::string word;
        std::string name;
        int value;
        int count=0;
        bool b{false};
        while(std::getline(iss,word,',')){
            std::cout<<word<<std::endl;
            count++;
            if (count==1) name=word;
            if (count==2){
                std::stringstream(word)>>value;
            }
        }
        if  (count!=2) {
            std::cerr<<"Invalid input "<<std::endl;
            exit(1);
        }
        std::cout<<b<<std::endl;
        std::cout<<name<<"=>"<<value<<std::endl;
    }

    return 0;
}