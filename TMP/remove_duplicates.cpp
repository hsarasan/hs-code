/* Remove adjacent duplicates from a sorted vector 
Usage : uniq<vector<1,2,3,3,4,4,5,5,7>>::type=vector<1,2,3,4,5,7>
test case
std::static_assert(std::is_same_v<uniq<vector<1,2,3,3,4,4,5,5,7>>,vector<1,2,3,4,5,7>>>);
*/
#include <iostream>
#include <type_traits>
#include <vector>

template <typename InputVector, typename OutputVector=std::vector<int>>
struct uniq{

};
int main(){

}


