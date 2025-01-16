#include <iostream>
#include <libmemcached/memcached.h>
#include <exception>
#include <string>

using namespace std;

class MemCacheProxy{

	public:
		MemCacheProxy(){
    	instance = memcached_create(nullptr);
    	servers = memcached_server_list_append(nullptr, "127.0.0.1", 11211, &rc);
    	rc = memcached_server_push(instance, servers);
    	memcached_server_list_free(servers);
    	if (rc != MEMCACHED_SUCCESS) {
        std::cerr << "Error adding server: " << memcached_strerror(instance, rc) << std::endl;
        memcached_free(instance);
				throw std::runtime_error("Instantiaion failed ");
    	}
		}
		MemCacheProxy(const MemCacheProxy& )=delete;
		MemCacheProxy & operator=(const MemCacheProxy&) = delete;
		~MemCacheProxy(){
    	memcached_free(instance);
		}

		void put(string key, string value){
			rc = memcached_set(instance,key.c_str(),key.length(),value.c_str(),value.length(),0,0);
			if (rc != MEMCACHED_SUCCESS) {
        throw std::runtime_error(memcached_strerror(instance,rc));
      }
    }

		string get(string key){
    	size_t value_length;
    	uint32_t flags;
    	char *retrieved_value = memcached_get(instance, key.c_str(), key.size(), &value_length, &flags, &rc);
			if (rc != MEMCACHED_SUCCESS){
        throw std::runtime_error(memcached_strerror(instance,rc));
			}
			std::string value(retrieved_value,value_length);
			free(retrieved_value);
			return value;
		}

	private:
		memcached_st * instance;		
    memcached_return_t rc;
    memcached_server_st *servers;

};
