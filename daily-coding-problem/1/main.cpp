#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>

using namespace std;


bool twoSum(vector<int> arr, int k){
    unordered_map<int, int> map;
    for(int i = 0; i < arr.size(); i++){
        if(map.find(k - arr[i]) != map.end()){
            return true;
        }
        map[arr[i]] = i;
    }
    return false;
}

int main(){

    assert(twoSum({4,7,1,-3,2}, 5) == true);
    assert(twoSum({4,7,1,-3,2}, 10) == false);
    assert(twoSum({4,7,1,-3,2}, 3) == true);
    return 0;
}