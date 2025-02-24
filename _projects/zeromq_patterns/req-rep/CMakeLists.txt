cmake_minimum_required(VERSION 3.10)
project(RequestReply)

set(CMAKE_CXX_STANDARD 17)

# Find dependencies ZeroMQ
find_package(PkgConfig REQUIRED)
find_package(ZeroMQ REQUIRED)
pkg_check_modules(ZeroMQ REQUIRED libzmq)

# Include the directories for ZeroMQ 
include_directories(${ZeroMQ_INCLUDE_DIRS} include)

# Include the directory with the generated files
include_directories(${CMAKE_BINARY_DIR})


# Create the producer executable
add_executable(producer producer.cpp)
target_link_libraries(producer ${ZeroMQ_LIBRARIES} )

# Create the consumer executable
add_executable(consumer consumer.cpp)
target_link_libraries(consumer ${ZeroMQ_LIBRARIES})
