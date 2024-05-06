#include <iostream>
#include <cstring>

class mystring{
    char * data;
    public:
        mystring(const char * _charPtr)  { 
            std::cout<<"ctor"<<std::endl;
            int sz=std::strlen(_charPtr);
            data = new char(sz+1);
            memcpy(data, _charPtr, sz);
            data[sz]=0;
        }
        bool operator==(const char *rhs){
            return true;
        }
        mystring (const mystring & rhs){
            std::cout<<"copy ctor"<<std::endl;
            data=rhs.data;
        }
        mystring (mystring && rhs){
            std::cout<<"Move ctor "<<std::endl;
            data=std::move(rhs.data);
        }
        mystring & operator=(const mystring & rhs){
            std::cout<<"Operator="<<std::endl;
            auto temp(rhs);
            swap(temp);
            return *this;
        }
        mystring & operator=(mystring &&rhs){
            std::cout<<"Operator move"<<std::endl;
            auto temp = std::move(rhs);
            swap(temp);
            return *this;
        }
        void swap(mystring &rhs) noexcept{
            auto temp = rhs.data;
            rhs.data=data;
            data=temp;
        }
        friend std::ostream & operator<<(std::ostream&, const mystring&);
};

std::ostream& operator<<(std::ostream & o, const mystring & obj){
    o<<obj.data;
    return o;
}

int main(){
    mystring x1("object to copy");
    mystring x2("object to move");
    mystring x3("object for copy operator");
    mystring x4("obj for move operator");
    auto x_copy = x1;
    auto x_move = std::move(x2);
    std::cout<<x_copy<<" "<<x_move<<std::endl;
    x_copy = x3;
    x_move = std::move(x4);
    std::cout<<x_copy<<" "<<x_move<<std::endl;
    return 0;

}