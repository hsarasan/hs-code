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

class ThreadGuard{

	std::thread &thr;
	public:
		explicit ThreadGuard(std::thread & tid):thr(tid){}
		ThreadGuard ( const ThreadGuard & )=delete;
		ThreadGuard & operator=( const ThreadGuard & )=delete;
		~ThreadGuard(){
			if (thr.joinable()) thr.join();
		}

};

class Callable{
	public:
		void execute(int i){
			std::cout<<"going to sleep"<<std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(i));
			std::cout<<"exiting"<<std::endl;
	}
};
int main(){

	Callable call;
  std::thread tid(&Callable::execute,&call,10);	
	ThreadGuard tg(tid);
}
