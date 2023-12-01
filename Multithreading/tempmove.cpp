#include <iostream>
#include <memory>
#include <string>
#include <cstring>

class Resource{

    char * data{nullptr};
    public :
    Resource(std::string s)
    {
        std::cout<<"Main Ctr"<<std::endl;
        data = new char[s.size()+1];
        strcpy(data, s.c_str());
    }
    Resource(const Resource& rhs)
    {
        std::cout<<"Copy Ctr"<<std::endl;
        if (rhs.data)
        {
            data = new char[ strlen(rhs.data) ];
            strcpy(data, rhs.data);
        }
    }
    Resource & operator=(const Resource& rhs) =delete;
    void print() 
    {
        std::cout<<"Resource=>"<<(void*)data<<"=>"<<data<<std::endl;
    }
    ~Resource()
    {
        delete []data;
        data = nullptr;
    }
};

class Widget{
    std::unique_ptr<Resource>  ptr;
    public:
        Widget(std::string &s){
            ptr = std::make_unique<Resource>(s);
        }  
        Widget(const Widget& rhs)
        {
            if (rhs.ptr) ptr =  std::make_unique<Resource>(*rhs.ptr);
        }
        Widget & operator=(const Widget & rhs)
        {
            if (&rhs!=this) 
            {
                Widget temp(rhs);
                *this = temp;
            }
            return *this;
        }
        Widget & operator=(Widget && rhs)
        {
            if (&rhs!=this) 
            {
                ptr = std::move(rhs.ptr);
            }
            return *this;
        }
        void print() 
        {
            ptr->print();
        }
};

int main()
{
    auto a = std::string("abc");
    Widget w(a);
    w.print();
    auto w2 = w;
    w2.print();
    return 0;
}