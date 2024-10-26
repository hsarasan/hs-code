#include <iostream>
#include <memory>
#include <thread>
#include <string>
#include <vector>

using namespace std;

class Observer{
    public:
        virtual void processEvent(string event)=0;
};
class Subject{
    vector<weak_ptr<Observer>> observers;
    public:
        void addObserver(shared_ptr<Observer>  o){
            weak_ptr<Observer> wptr = o;
            observers.push_back(wptr);
        }
        void propogateEvent(string event){
            for (const auto & observer: observers){
                auto shPtr = observer.lock();
                if (shPtr) shPtr->processEvent(event);
            }
        }
};

class ConcreteObserver: public Observer{
    string observer_name;
    public:
        ConcreteObserver(string name):observer_name(name){}
        void processEvent(string event) override {
            cout<<"Event "<<event<<" processed by "<<observer_name<<endl;
        }
};

int main(){

    auto first_observer = make_shared<ConcreteObserver>("first");
    auto second_observer = make_shared<ConcreteObserver>("second");
    Subject subject;
    subject.addObserver(first_observer);
    subject.addObserver(second_observer);
    subject.propogateEvent("event-1");
    subject.propogateEvent("event-2");
    first_observer.reset();
    subject.propogateEvent("event-3");
    second_observer.reset();
    subject.propogateEvent("event-4");
}