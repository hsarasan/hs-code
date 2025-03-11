#include <iostream>
#include <vector>
#include <deque>

using namespace std;
void printMaxInK(const vector<int> & nums, int k){
    deque<int> dq;
    int n=nums.size();
    dq.push_back(nums[0]);
    for (int i=1;i<n;++i){
        if (i>k && !dq.empty()) dq.pop_front();
        while(!dq.empty() && dq.back()<nums[i]) dq.pop_back();
        dq.push_back(nums[i]);
        if (i>=k-1)
            cout<<dq.front()<<endl;
    }
}

int main(){
    printMaxInK({10,8,8,4,6},3);
    printMaxInK({1,2,3,4,5,6},3);
    return 0;
}