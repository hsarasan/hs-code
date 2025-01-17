cmake_minimum_required(VERSION 3.10)
project(ProtobufProducer)

set(CMAKE_CXX_STANDARD 17)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Use pkg-config to find Protobuf
pkg_check_modules(Protobuf REQUIRED protobuf)
include_directories(${Protobuf_INCLUDE_DIRS})
link_directories(${Protobuf_LIBRARY_DIRS})

# Avoid RPATH issues on some systems
add_definitions(${Protobuf_CFLAGS_OTHER})

# Add the producer executable
add_executable(producer producer.cpp message.pb.cc)
target_link_libraries(producer ${Protobuf_LIBRARIES})


# Add the producer executable
add_executable(consumer consumer.cpp message.pb.cc)
target_link_libraries(consumer ${Protobuf_LIBRARIES})
