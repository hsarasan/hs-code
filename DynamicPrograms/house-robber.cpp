/*

Given an array of integers arr where arr[i] represents the amount of money in the house i, you are asked to find the maximum amount of money that a robber can steal knowing that he can't steal two adjacent houses because the security systems would automatically call the police



Example:
input: arr = [2, 10, 3, 6, 8, 1, 7]
output: 25
*/

/*

    condition: n>3
    f(n)=std::max( f(n-1), f(n-2)+arr[n-1], f(n-3)+arr[n-2], f(n-3)+arr[n-1]);

*/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

std::map<int,int> dp_table;

int lookup(int n){
    if (dp_table.count(n) ) return dp_table[n];
    return -1;
}
void store(int n,int value){
    dp_table[n]=value;
}

void initialise(std::vector<int> &input) {
    store(0,0);
    store(1,input[0]);
    store(2,std::max(input[1],input[0]));

}
void printDPTable()
{
    for (const auto & [k,v]: dp_table)
        std::cout<<k<<"="<<v<<std::endl;
}
int solution(std::vector<int> input) {
    int n = input.size();
    if (input.size()==0) return 0;
    if (input.size()==1) return input[0];
    if (input.size()==2) return std::max(input[0],input[1]);
    initialise(input);    
    for (int i=3;i<n+1;++i){
        int n3 = lookup(i-3);
        int n2 = lookup(i-2);
        int n1 = lookup(i-1);
        int v1 = std::max(n1,n2+input[i-1]);
        int v2 = std::max(n3+input[i-2],n3+input[i-1]);
        int value = std::max(v1,v2);
        store(i,value);
    }
    int ret = lookup(n);
    return ret;
}
int main() {
    std::vector<int> arr{2, 10, 3, 6, 8, 1, 7};
    int best=solution(arr);
    std::cout<<"Best returns="<<best<<std::endl;
    return 0;
}

