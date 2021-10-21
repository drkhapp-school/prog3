cmake_minimum_required(VERSION 3.1)
project(atelier3)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include")

# Include headers
include_directories(include)

# Include source files
file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
