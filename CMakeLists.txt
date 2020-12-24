cmake_minimum_required(VERSION 3.10)

# specify the C++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

# set the project name
project(patterns)

# add sub-directories
add_subdirectory(common)
add_subdirectory(abstract_factory)
add_subdirectory(factory_method)
