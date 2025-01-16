#include <iostream>
#include <hiredis/hiredis.h>

int main() {
    // Connect to Redis
    redisContext *c = redisConnect("127.0.0.1", 6379);
    
    if (c == NULL || c->err) {
        if (c) {
            std::cerr << "Connection error: " << c->errstr << std::endl;
        } else {
            std::cerr << "Can't allocate redis context" << std::endl;
        }
        return 1;
    }

    // Set a key-value pair in Redis
    const char *key = "mykey";
    const char *value = "Hello, Redis!";
    redisReply *reply = (redisReply*)redisCommand(c, "SET %s %s", key, value);
    
    if (reply == NULL) {
        std::cerr << "Redis command failed" << std::endl;
        return 1;
    }
    
    std::cout << "SET command response: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Get the value from Redis by key
    reply = (redisReply*)redisCommand(c, "GET %s", key);
    
    if (reply == NULL) {
        std::cerr << "Redis command failed" << std::endl;
        return 1;
    }
    
    std::cout << "GET command response: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Disconnect from Redis
    redisFree(c);

    return 0;
}
