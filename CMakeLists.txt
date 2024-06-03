cmake_minimum_required(VERSION 3.0)
project(mymoduo)

aux_source_directory(. SRC_LIST)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

add_library(mymuduo SHARED ${SRC_LIST})

# target_link_libraries(mymuduo )

