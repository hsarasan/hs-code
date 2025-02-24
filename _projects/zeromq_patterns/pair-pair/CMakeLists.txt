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

# Create the server executable
add_executable(server server.cpp)
target_link_libraries(server ${ZeroMQ_LIBRARIES} )

# Create the client executable
add_executable(client client.cpp)
target_link_libraries(client ${ZeroMQ_LIBRARIES} )
