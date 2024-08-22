#include <iostream>
#include <functional>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <array>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <thread>
using namespace std;

class Callable{
	public:
		void execute(int i){
			std::cout<<"going to sleep"<<std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(i));
			std::cout<<"exiting"<<std::endl;
	}
};

void f(int i){
}
int main(){
	std::cout<<"No of concurrent threads that can be run is "<<std::thread::hardware_concurrency()<<std::endl;
}
