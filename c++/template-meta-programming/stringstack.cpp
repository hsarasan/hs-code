#include <iostream>
#include <stack>

template <>
class std::stack<std::string> {
    public:
        void push(const std::string &c){
            std::cout<<"Not implemented "<<std::endl;
        }

};

int main(){
    std::stack<int> ST;
    std::stack<std::string> ST2;
    ST.push(1);
    ST2.push(std::string("abc"));
    return 0;
}