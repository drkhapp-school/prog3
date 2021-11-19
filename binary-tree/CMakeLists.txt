cmake_minimum_required(VERSION 3.1)
project(binary_search_tree)

set (CMAKE_CXX_STANDARD 17)

# Include source files
file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
