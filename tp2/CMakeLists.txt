cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -framework SDL2 -framework SDL2_image -framework SDL2_ttf -F /Library/Frameworks -I /Library/Frameworks/SDL2.framework/Headers -I /Library/Frameworks/SDL2_image.framework/Headers -I /Library/Frameworks/SDL2_ttf.framework/Headers") 
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/")

project(tp2)

# Include source files
file(GLOB SOURCES "src/*.cpp")
find_library(LIB420C35JOTP3 420C35JOTP3 include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIB420C35JOTP3}) 
