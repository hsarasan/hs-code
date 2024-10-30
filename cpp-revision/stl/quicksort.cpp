#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <type_traits>

using namespace std;

template <typename iterator>
void quicksort(iterator first, iterator last){
    if (first==last) return;
    //using vtype = typename std::iterator_traits<iterator>::value_type;
    //copy(first,last,ostream_iterator<vtype>(cout,","));
    //cout<<endl;
    auto dist = std::distance(first,last);
    auto pivot_iter = first;
    std::advance(pivot_iter,dist/2);
    auto pivot = *pivot_iter;
    //cout<<"Pivot = "<<pivot<<endl;

    auto less_than_pivot = [pivot](const int & val){ return val<pivot;};
    auto middle_1 = std::partition(first,last,less_than_pivot);
    //copy(first,middle_1,ostream_iterator<vtype>(cout,","));
    //cout<<endl;

    auto not_less_than_pivot = [pivot](const int & value){return !(value>pivot);};
    auto middle_2 = std::partition(middle_1,last,not_less_than_pivot);
    //copy(middle_1,last,ostream_iterator<vtype>(cout,","));
    //cout<<endl;
    quicksort(first,middle_1);
    quicksort(middle_2,last);

}



int main(){

    int array[]={3,5,1,6,2};
    quicksort(std::begin(array),std::end(array));
    for (int i=0;i<5;++i) {
        cout<<array[i]<<",";
    }
    return 0;
}