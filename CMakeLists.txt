cmake_minimum_required(VERSION 3.10)

# specify the C++ compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")

# set the project name
project(patterns)

# store all item in current dir into variable "children"
file(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
# remove item with names ".git" and "build"
list(REMOVE_ITEM children .git build)
# loop throw items
FOREACH(child ${children})
  # process only if item is a directory
  IF(IS_DIRECTORY ${child})
    message("Processing ${child}")
    add_subdirectory(${child})
  ENDIF()
ENDFOREACH()
