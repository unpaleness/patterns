cmake_minimum_required(VERSION 3.10)

# specify the C++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

# set the project name
project(patterns)

# set binary directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/)

# add sub-directory with common code
add_subdirectory(common)

# store all item in dir "patterns" into variable "children"
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} patterns/*)
# loop throw items
FOREACH(child ${children})
  # process only if item is a directory
  IF(IS_DIRECTORY ${child})
    message("Processing ${child}")
    add_subdirectory(${child})
  ENDIF()
ENDFOREACH()
