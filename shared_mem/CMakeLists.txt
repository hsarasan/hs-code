cmake_minimum_required(VERSION 3.10)

# Project name
project(SharedMemoryIPC)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable targets
add_executable(producer producer.cpp)
add_executable(consumer consumer.cpp)
add_executable(producer_s producer_sem.cpp)
add_executable(consumer_s consumer_sem.cpp)

# Link against the real-time library (needed for shm_open and shm_unlink)
target_link_libraries(producer rt)
target_link_libraries(consumer rt)
target_link_libraries(producer_s rt pthread)
target_link_libraries(consumer_s rt pthread)
