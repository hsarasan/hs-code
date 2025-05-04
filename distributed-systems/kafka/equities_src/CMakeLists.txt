cmake_minimum_required(VERSION 3.10)
project(equities_tools)

set(CMAKE_CXX_STANDARD 17)

# Find librdkafka++ and librdkafka
find_package(PkgConfig REQUIRED)
pkg_check_modules(RDKAFKA REQUIRED rdkafka++ rdkafka)

include_directories(${RDKAFKA_INCLUDE_DIRS})
link_directories(${RDKAFKA_LIBRARY_DIRS})

# Common Kafka libraries
set(KAFKA_LIBS rdkafka++ rdkafka)

# md-ingest executable
add_executable(md-ingest src/md_ingest.cpp)
target_include_directories(md-ingest PRIVATE ${RDKAFKA_INCLUDE_DIRS})
target_link_libraries(md-ingest ${KAFKA_LIBS})

# price-engine executable
add_executable(price-engine src/price_engine.cpp)
target_include_directories(price-engine PRIVATE ${RDKAFKA_INCLUDE_DIRS})
target_link_libraries(price-engine ${KAFKA_LIBS})

