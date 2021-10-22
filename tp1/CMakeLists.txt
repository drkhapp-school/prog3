cmake_minimum_required(VERSION 3.21)
project(tp1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-isysroot /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include -w -framework SDL2 -framework SDL2_image -framework SDL2_ttf -F /Library/Frameworks -L/Users/darkhappy/Repositories/prog/prog3/tp1/include/ -l420C35JOTP1 -I /Library/Frameworks/SDL2.framework/Headers -I /Library/Frameworks/SDL2_image.framework/Headers -I /Library/Frameworks/SDL2_ttf.framework/Headers") 

# Include source files
file(GLOB SOURCES "src/*.cpp")

message(${SDL2_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
