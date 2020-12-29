# loop throw patterns types
file (GLOB pattern_types RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
# loop throw items
foreach (pattern_type ${pattern_types})
    # process only if item is a directory
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${pattern_type})
        message ("Processing pattern type \"${pattern_type}\"")
        add_subdirectory (${pattern_type})
    endif ()
endforeach ()
