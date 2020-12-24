#set include directories
include_directories(../common/include)

# add executables
add_executable(builder src/main.cpp src/pattern.cpp)

# link libraries
target_link_libraries(builder common)
