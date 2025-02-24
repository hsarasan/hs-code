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


# Create the publisher executable
add_executable(publisher publisher.cpp)
target_link_libraries(publisher ${ZeroMQ_LIBRARIES} )

# Create the subscriber executable
add_executable(subscriber subscriber.cpp)
target_link_libraries(subscriber ${ZeroMQ_LIBRARIES})

# Create the news publisher executable
add_executable(newspublisher newspublisher.cpp)
target_link_libraries(newspublisher ${ZeroMQ_LIBRARIES} )

# Create the newssubscriber executable
add_executable(newssubscriber newssubscriber.cpp)
target_link_libraries(newssubscriber ${ZeroMQ_LIBRARIES})
