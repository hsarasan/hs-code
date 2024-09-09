#include <iostream>

using namespace std;

class CurrentPaymentProcesser {

    public:
        virtual void pay(int amount){
            std::cout<<"Current PP "<<amount<<std::endl;
        }
};

class StripePaymentProcessor{
    public:
        void makePayment(int amount){
            std::cout<<"Stripe payment "<<std::endl;
        }
};

void client(CurrentPaymentProcesser & pp, int amount){
    pp.pay(amount);
}

class CPPToStripeAdapter : public CurrentPaymentProcesser{
    public:
    StripePaymentProcessor sp;
    CPPToStripeAdapter(StripePaymentProcessor sp_):sp(sp_){}
    void pay(int amount){
        sp.makePayment(amount);
    }
};

int main(){
    StripePaymentProcessor stripe;
    CPPToStripeAdapter cpp(stripe);
    client(cpp,100);

}
