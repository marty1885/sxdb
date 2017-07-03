cmake_minimum_required (VERSION 2.6)

project(sxdb)
project(sample)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -std=c++11")

include_directories(include)

find_package(TinyXML2 REQUIRED)

#main linrary
add_library(sxdb SHARED src/sxdb.cpp)
include_directories(${TINYXML2_INCLUDE_DIRS})
target_link_libraries(sxdb ${TINYXML2_LIBRARIES})

add_executable(sample sample/sample.cpp)
target_link_libraries(sample sxdb)
