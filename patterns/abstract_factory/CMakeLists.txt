#set include directories
include_directories(../../common/include)

# add executables
add_executable(abstract_factory src/main.cpp src/pattern.cpp)

# link libraries
target_link_libraries(abstract_factory common)
