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


# Create the router executable
add_executable(router router.cpp)
target_link_libraries(router ${ZeroMQ_LIBRARIES} )

# Create the worker executable
add_executable(worker worker.cpp)
target_link_libraries(worker ${ZeroMQ_LIBRARIES})

# Create the news router executable
add_executable(dealer dealer.cpp)
target_link_libraries(dealer ${ZeroMQ_LIBRARIES} )
