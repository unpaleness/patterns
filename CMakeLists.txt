cmake_minimum_required (VERSION 3.12)

# set the project name
project (patterns)

# specify the C++ compiler flags
if (MSVC)
    set (CMAKE_CXX_FLAGS "/W4 /O2 /std:c++17 /EHsc")
else ()
    set (CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")
endif ()

# set binary directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../../bin/)

# add sub-directory with common library
add_subdirectory (common)

# add sub-directory with patterns types
add_subdirectory (patterns)
