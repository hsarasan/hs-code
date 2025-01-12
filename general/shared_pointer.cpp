#include <iostream>
#include <atomic>
#include <cassert>

template <typename T>
class SharedPtr{

	int * pCounter;
  T * object;

  public:


  SharedPtr(T * ptr) { 
		object=ptr; 
		pCounter = new int(1);
	}
  SharedPtr(const SharedPtr & rhs) { 
			pCounter=rhs.pCounter;
			(*pCounter)++;
			object = rhs.object;
	}
	SharedPtr(SharedPtr && rhs)noexcept {
	  object=nullptr;
		swap(rhs,*this);
	}
	SharedPtr & operator=(const SharedPtr & rhs) {
		auto temp=rhs;
		swap(temp,*this);
		return *this;
	}

	SharedPtr & operator=(SharedPtr && rhs) noexcept{
		auto temp=std::move(rhs);
		swap(temp,*this);
		return *this;
	}
	friend void swap(SharedPtr & lhs, SharedPtr &rhs){
		using std::swap;
	  std::swap(rhs.object,lhs.object);
		std::swap(rhs.pCounter, lhs.pCounter);	
	}

	int get_count(){
		return *pCounter;
	}
	T& operator*(){ 
		return *object;
	}
	T * operator->(){
		return object;
	}
	T * get(){
		return object;
	}
	void reset(T * ptr=nullptr){
		SharedPtr temp(ptr);
		swap(temp,*this);
	}
  ~SharedPtr() {
    (*pCounter)--;
		if (*pCounter==0) {
			std::cout<<"Deleting "<<std::endl;
			if (object) delete object;
			delete pCounter;
		}
	}
};

int main(){

	//test constructor
	SharedPtr<int> shp(new int(20));
	assert(shp.get_count()==1);

	//test copy constructor
	auto shp2 = shp;
	assert(shp.get_count()==2);
	assert(shp2.get_count()==2);

	//test dereferencing
  int x = *shp;
	assert(x==20);

	//test swap
	SharedPtr<int> other(new int(30));
	assert(other.get_count()==1);
  swap(other,shp);	
	assert(other.get_count()==2);
	assert(shp.get_count()==1);
	assert(shp2.get_count()==2);
  swap(other,shp);	
	assert(other.get_count()==1);
	assert(shp.get_count()==2);
	assert(shp2.get_count()==2);

	//test move
	auto other2=std::move(other);
	assert(other.get()==nullptr);
	assert(other2.get_count()==1);
	

	//test move operator
	other = std::move(other2);
	assert(other2.get()==nullptr);
	assert(other.get_count()==1);

	other=shp2;
	assert(other.get_count()==3);
	assert(shp2.get_count()==3);

	//testing reset(nullptr)
	other.reset();
	assert(shp2.get_count()==2);

	auto other3=shp2;
	assert(other3.get_count()==3);

  other3.reset(new int(60));	
	assert(other3.get_count()==1);
	assert(shp2.get_count()==2);

}
