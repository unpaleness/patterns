cmake_minimum_required(VERSION 3.10)

# specify the C++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

# set the project name
project(patterns)

# add library from source files
add_library(lib_methods
    src/factory_method/method.cpp
)

# add the executable
add_executable(patterns src/main.cpp)

#set include directories for executable
target_include_directories(patterns PUBLIC src)

# link libraries
target_link_libraries(patterns lib_methods)

