#set include directories
include_directories (include)

# add libraries from source files
if (MSVC)
    add_library (common src/shapes.cpp src/platform.cpp src/windows.cpp)
else ()
    add_library (common src/shapes.cpp src/platform.cpp src/unix.cpp)
endif ()
