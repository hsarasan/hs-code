#include <iostream>
#include <cstring>
#include <memory>

struct StringValue{
    char * data;
    ~StringValue(){
        std::cout<<"Deleting SV "<<data<<std::endl;
    }
};

class RCString{
    std::shared_ptr<StringValue> pSV;
    public:
        RCString(const char * rhs){
            pSV=std::make_shared<StringValue> ();
            int size=std::strlen(rhs);
            pSV->data = new char[size+1];
            std::strcpy(pSV->data, rhs);
            pSV->data[size]=0;
        }
        RCString(const RCString & rhs){
            pSV=rhs.pSV;
        }
        RCString& operator=(const RCString &rhs){
            RCString temp(rhs);
            std::swap(pSV, temp.pSV);
            return *this;
        }
        RCString (RCString && rhs){
            pSV=std::move(rhs.pSV);
        }
        RCString & operator=(RCString &&rhs){
            RCString temp = std::move(rhs);
            std::swap(pSV, temp.pSV);
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& , const RCString &);
};

std::ostream& operator<<(std::ostream& o, const RCString & str){
    o<<str.pSV->data;
    return o;
}

void copy(){
    RCString str1("abc");
    RCString str2("str2");
    RCString str3(str2);
    RCString str4("str4");
    str1 = str3;
    str4=str4;
    std::cout<<str1<<std::endl;
    std::cout<<str3<<std::endl;
    std::cout<<str4<<std::endl;
}

void move(){
    RCString str1("abc");
    RCString str2("str2");
    RCString str3(std::move(str2));
    RCString str4("str4");
    std::cout<<str1<<std::endl;
    std::cout<<str3<<std::endl;    
    str1 = std::move(str3);
    str4=std::move(str4);
    std::cout<<str1<<std::endl;
    std::cout<<str4<<std::endl;
}

int main(){
    move();
    return 0;
}