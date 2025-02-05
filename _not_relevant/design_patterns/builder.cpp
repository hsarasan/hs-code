#include <iostream>

using namespace std;

//product
class House{
    int windows{0};
    int doors{0};
    bool roof{false};
    string architecture_style;
    public:
        House(string s):architecture_style(s){}
        void setDoors(int x){doors=x;}
        void setWindows(int x){windows=x;}
        void setRoof(){roof=true;}
        void show(){
            std::cout<<"House with "<<doors<<" doors, "<<windows<<" windows "<<roof<<" roof "<<"arch style "<<architecture_style<<std::endl;
        }
};
class AbstractBuilder{
    public:
        virtual House constructHouse()=0;
};
class GreekStyleHouseBuilder: public AbstractBuilder{
    public:
        House constructHouse(){
            House h("GreekStyle ");
            h.setDoors(3);
            h.setRoof();
            h.setWindows(10);
            return h;
        }
};


class Director{
    AbstractBuilder *builder;
    public:
        Director(AbstractBuilder *builder_):builder(builder_){}
        House construct(){
            return builder->constructHouse();

        }
};


//client code
int main(){
    GreekStyleHouseBuilder greekHouseBuilder;
    Director director(&greekHouseBuilder);
    House greek_house = director.construct();
    greek_house.show();
}