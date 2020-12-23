cmake_minimum_required(VERSION 3.10)

# set the project name
project(patterns)

# specify the C++ standard
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

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

