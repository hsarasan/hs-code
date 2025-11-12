cmake_minimum_required(VERSION 3.14)
project(plugin_demo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
    main.cpp
    plugin_manager.cpp
)

add_executable(plugin_app ${SOURCE_FILES})

target_include_directories(plugin_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
    target_compile_options(plugin_app PRIVATE /W4 /permissive-)
else()
    target_compile_options(plugin_app PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Install target (optional)
install(TARGETS plugin_app RUNTIME DESTINATION bin)
