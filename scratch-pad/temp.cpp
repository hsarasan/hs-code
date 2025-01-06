#include <iostream>
#include <memory>
#include <string>
#include <exception>


using namespace std;
class HotDrinkFactory;
struct HotDrink{};
struct Tea: public HotDrink{
    Tea(){
        cout<<"add tea bag, hot water "<<endl;
    }
    friend class HotDrinkFactory;
};
struct Coffee: public HotDrink{

    Coffee(){
        cout<<"add coffee pod, hot water and brew "<<endl;
    }
    friend class HotDrinkFactory;
};

struct HotDrinkFactory{
    private :
        HotDrinkFactory(){}
    public:
        static HotDrinkFactory instance(){
            static HotDrinkFactory Instance;
            return Instance;
        }
    unique_ptr<HotDrink> make_hot_drink(string drink_type){
        if (drink_type=="tea"){
            return make_unique<Tea>();
        }
        else if (drink_type=="coffee"){
            return make_unique<Coffee>();
        }
        throw std::runtime_error("not known drink");
    }   
};

int main(){
    auto t=HotDrinkFactory::instance().make_hot_drink("tea");
    auto c=HotDrinkFactory::instance().make_hot_drink("coffee");
    try{
        auto w=HotDrinkFactory::instance().make_hot_drink("whiskey");
    }
    catch (std::exception &e){
        cout<<e.what()<<endl;
    }
    return 0;
}