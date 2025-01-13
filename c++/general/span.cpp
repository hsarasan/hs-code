#include <iostream>
#include <vector>
#include <span>

using namespace std;

void func(std::span<int> nums){
    for (auto n: nums)
        cout<<n<<endl;
}

int main(){
    vector<int> v{1,2,3,4,5};
    func(v);
}