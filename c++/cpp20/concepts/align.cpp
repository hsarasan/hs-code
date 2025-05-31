#include <iostream>

using namespace std;

template <int val>
concept power_of_two=has_single_bit< static_cast<unsigned> (val)>;

template <int val>
requires power_of_two<val>
struct Memory{

};

int main(){

    return 0;
}