#include "memcacheproxy.h"


int main(){


	MemCacheProxy memcache;
	MemCacheProxy memcache2;
	memcache.put("1","one");
	cout<<memcache.get("1");
	memcache.put("1","two");
	cout<<memcache2.get("1");

}
