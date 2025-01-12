#include <memory>

using namespace std;

class Implementation;
struct Interface{
    
    Interface(unique_ptr<Implementation>  impl):pImpl(move(impl)){}
    unique_ptr<Implementation> pImpl;
    void execute();
};