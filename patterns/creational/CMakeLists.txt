# loop throw patterns
file (GLOB patterns RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
# loop throw items
foreach (pattern ${patterns})
    # process only if item is a directory
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${pattern})
        message ("Processing pattern \"${pattern}\"")
        add_subdirectory (${pattern})
    endif ()
endforeach ()
