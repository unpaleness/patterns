cmake_minimum_required(VERSION 3.10)

# specify the C++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

# set the project name
project(patterns)

#set include directories
include_directories(common/include)

# add libraries from source files
add_library(common common/src/square.cpp)

# add executables
add_executable(abstract_factory abstract_factory/src/main.cpp abstract_factory/src/pattern.cpp)
add_executable(factory_method factory_method/src/main.cpp factory_method/src/pattern.cpp)

# link libraries
target_link_libraries(abstract_factory common)
target_link_libraries(factory_method common)

