cmake_minimum_required (VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/utility)
add_definitions(-w)
aux_source_directory(. DIR_SRCS)
add_executable(main ${DIR_SRCS})

set(CMAKE_CXX_FLAGS "-g -std=c++14")
