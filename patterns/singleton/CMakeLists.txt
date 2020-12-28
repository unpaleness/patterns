set(pattern_name "singleton")

if (UNIX)
    # add executables
    add_executable(${pattern_name} src/main.cpp src/pattern.cpp)
    # add cmake link flags
    set_target_properties(${pattern_name} PROPERTIES LINK_FLAGS "-pthread")
else()
    message("Pattern \"${pattern_name}\" is not supported for this platform")
endif()
