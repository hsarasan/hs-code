cmake_minimum_required(VERSION 3.10)
project(ZeroMQProtobufExample)

set(CMAKE_CXX_STANDARD 17)

# Find dependencies (ZeroMQ and Protobuf)
find_package(PkgConfig REQUIRED)
pkg_check_modules(Protobuf REQUIRED protobuf)


find_package(ZeroMQ REQUIRED)
pkg_check_modules(ZeroMQ REQUIRED libzmq)

# Include the directories for ZeroMQ and Protobuf
include_directories(${Protobuf_INCLUDE_DIRS} ${ZeroMQ_INCLUDE_DIRS} include)
link_directories(${Protobuf_LIBRARY_DIRS})

# Avoid RPATH issues on some systems
add_definitions(${Protobuf_CFLAGS_OTHER})

# Set the path to the .proto file
set(PROTO_FILE ${CMAKE_SOURCE_DIR}/message.proto)
set(GENERATED_FILES ${CMAKE_BINARY_DIR}/message.pb.cc ${CMAKE_BINARY_DIR}/message.pb.h)

# Add a custom command to run protoc and generate .pb.cc and .pb.h files
add_custom_command(
    OUTPUT ${GENERATED_FILES}
    COMMAND protoc --proto_path=${CMAKE_SOURCE_DIR} --cpp_out=${CMAKE_BINARY_DIR} ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
    COMMENT "Running protoc to generate C++ files from ${PROTO_FILE}"
    VERBATIM
)

# Add a custom target to ensure protoc is run before building
add_custom_target(GenerateProtobuf ALL DEPENDS ${GENERATED_FILES})

# Include the directory with the generated files
include_directories(${CMAKE_BINARY_DIR})


# Create the producer executable
add_executable(producer producer.cpp ${GENERATED_FILES})
add_dependencies(producer GenerateProtobuf)
target_link_libraries(producer ${ZeroMQ_LIBRARIES} ${Protobuf_LIBRARIES})

# Create the consumer executable
add_executable(consumer consumer.cpp ${GENERATED_FILES})
add_dependencies(consumer GenerateProtobuf)
target_link_libraries(consumer ${ZeroMQ_LIBRARIES} ${Protobuf_LIBRARIES})
