#include <bits/stdc++.h>

using namespace std;

class Light{
    public:
        void on(){
            cout<<"Light ON"<<endl;
        }
        void off(){
            cout<<"Lights OFF"<<endl;
        }
};

struct command{
    virtual void execute()=0;
};
struct LightsOn:public command{
    LightsOn(Light & l):light(l){
    }
    void execute(){ light.on();}
    Light & light;
};
struct LightsOff:public command{
    LightsOff(Light & l):light(l){
    }
    void execute(){ light.off();}
    Light & light;
};
struct Remote{
    void submit(command & c){
        c.execute();
    }
};


int main(){
    Light l;
    LightsOn lightson(l);
    Remote remote;
    remote.submit(lightson);
    LightsOff lightsoff(l);
    remote.submit(lightsoff);
    return 0;
}