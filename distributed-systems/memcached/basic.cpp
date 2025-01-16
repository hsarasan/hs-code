#include <iostream>
#include <libmemcached/memcached.h>

int main() {
    // Create a Memcached instance
    memcached_st *memc = memcached_create(nullptr);

    // Add Memcached server
    memcached_return_t rc;
    memcached_server_st *servers = memcached_server_list_append(nullptr, "127.0.0.1", 11211, &rc);
    rc = memcached_server_push(memc, servers);
    memcached_server_list_free(servers);

    if (rc != MEMCACHED_SUCCESS) {
        std::cerr << "Error adding server: " << memcached_strerror(memc, rc) << std::endl;
        memcached_free(memc);
        return 1;
    }
    // Set a key-value pair
    const char *key = "greeting";
    const char *value = "Hello, Memcached!";
    rc = memcached_set(memc, key, strlen(key), value, strlen(value), 0, 0);

    if (rc != MEMCACHED_SUCCESS) {
        std::cerr << "Error setting key: " << memcached_strerror(memc, rc) << std::endl;
    } else {
        std::cout << "Key set successfully!" << std::endl;
    }

    // Retrieve the value
    size_t value_length;
    uint32_t flags;
    char *retrieved_value = memcached_get(memc, key, strlen(key), &value_length, &flags, &rc);

    if (rc != MEMCACHED_SUCCESS) {
        std::cerr << "Error getting key: " << memcached_strerror(memc, rc) << std::endl;
    } else {
        std::cout << "Retrieved value: " << std::string(retrieved_value, value_length) << std::endl;
        free(retrieved_value);
    }

    // Clean up
    memcached_free(memc);

    return 0;
}
		
