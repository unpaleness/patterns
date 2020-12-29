set (pattern_name "singleton")

# add executables
add_executable (${pattern_name} src/main.cpp src/pattern.cpp)

# add cmake link flags
if (UNIX)
    set_target_properties (${pattern_name} PROPERTIES LINK_FLAGS "-pthread")
endif ()
