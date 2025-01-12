#include <iostream>
#include <mutex>
#include <thread>
#include <string>

int gThreadLockLevel(INT_MAX);

class HierarchicalMutex{

private: 
    int lockLevel;
    int previousLevel;
    std::mutex m;
    void isLockValid(){
        std::cout<<"Checking "<<lockLevel<<" "<<gThreadLockLevel<<std::endl;
        if (lockLevel >= gThreadLockLevel)
        {
            std::string err("Higher Level " + std::to_string(gThreadLockLevel) + " already  locked");
            throw std::runtime_error(err.c_str());
        }
    }

public:
    HierarchicalMutex(int level) {
        lockLevel = level;
    }
    void lock(){
        isLockValid();
        previousLevel = gThreadLockLevel;
        gThreadLockLevel = lockLevel;
        m.lock();
    }
    void unlock(){
        gThreadLockLevel = previousLevel;
        m.unlock();
    }

};

int main() {

        HierarchicalMutex m1(1000);
        HierarchicalMutex m2(1200);
        HierarchicalMutex m3(100);
        m1.lock();
        m2.lock();
        m3.lock();
    std::cout<<"All done"<<std::endl;
    return 0;
}