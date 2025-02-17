set(CMAKE_CXX_STANDARD 17)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Use pkg-config to find Protobuf
pkg_check_modules(Protobuf REQUIRED protobuf)
include_directories(${Protobuf_INCLUDE_DIRS})
link_directories(${Protobuf_LIBRARY_DIRS})

# Avoid RPATH issues on some systems
add_definitions(${Protobuf_CFLAGS_OTHER})

# Path to the .proto file
set(PROTO_FILE ${CMAKE_SOURCE_DIR}/message.proto)
set(GENERATED_FILES ${CMAKE_BINARY_DIR}/message.pb.cc ${CMAKE_BINARY_DIR}/message.pb.h)

# Add a custom command to run protoc
add_custom_command(
    OUTPUT ${GENERATED_FILES}
    COMMAND protoc --proto_path=${CMAKE_SOURCE_DIR} --cpp_out=${CMAKE_BINARY_DIR} ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
    COMMENT "Running protoc to generate C++ files from ${PROTO_FILE}"
    VERBATIM
)

# Add a custom target to trigger the command
add_custom_target(GenerateProtobuf ALL DEPENDS ${GENERATED_FILES})

# Include the directory with the generated files
include_directories(${CMAKE_BINARY_DIR})

# Add the producer executable
add_executable(producer producer.cpp ${GENERATED_FILES})
add_dependencies(producer GenerateProtobuf)

# Link the Protobuf library
target_link_libraries(producer ${Protobuf_LIBRARIES})

# Add the consumer executable
add_executable(consumer consumer.cpp ${GENERATED_FILES})
add_dependencies(consumer GenerateProtobuf)

# Link the Protobuf library
target_link_libraries(consumer ${Protobuf_LIBRARIES})
