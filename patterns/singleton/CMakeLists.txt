# add executables
add_executable(singleton src/main.cpp src/pattern.cpp)

# add cmake link flags
set_target_properties(singleton PROPERTIES LINK_FLAGS "-pthread")
