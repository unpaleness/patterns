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
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin/)

# add sub-directory with common library
add_subdirectory (common)

set (prefix "patterns/")
# store all item in dir "patterns" into variable "patterns_dirs"
file (GLOB patterns_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${prefix}*)
# loop throw items
foreach (pattern_dir ${patterns_dirs})
    # process only if item is a directory
    if (IS_DIRECTORY ${pattern_dir})
        message ("Processing ${pattern_dir}")
        add_subdirectory (${pattern_dir})
    endif ()
endforeach ()
