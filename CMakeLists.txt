cmake_minimum_required(VERSION 3.10)

# specify the C++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

# set the project name
project(patterns)

#set include directories
include_directories(src)

# add libraries from source files
add_library(common src/common/square.cpp)

add_library(abstract_factory src/abstract_factory/pattern.cpp)
add_library(factory_method src/factory_method/pattern.cpp)

# add the executable
add_executable(patterns src/main.cpp)

# link libraries
target_link_libraries(abstract_factory common)
target_link_libraries(factory_method common)

target_link_libraries(patterns factory_method abstract_factory)

