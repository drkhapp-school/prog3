cmake_minimum_required(VERSION 3.1)
project(file_dynamique)

set (CMAKE_CXX_STANDARD 11)

# Include headers
include_directories(include)

# Include source files
file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
