#set include directories
include_directories (../../common/include)

# add executables
add_executable (factory_method src/main.cpp src/pattern.cpp)

# link libraries
target_link_libraries (factory_method common)
