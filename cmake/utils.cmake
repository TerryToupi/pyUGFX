# Grouping files to keep the original file structure
function(group_sources_by_folder_from_list file_list base_dir)
    foreach(source IN LISTS ${file_list})
        get_filename_component(source_path "${source}" PATH)
        file(RELATIVE_PATH rel_path "${base_dir}" "${source_path}")
        string(REPLACE "/" "\\" group "${rel_path}")
        if(NOT group STREQUAL "")
            source_group("${group}" FILES "${source}")
        else()
            source_group("" FILES "${source}")
        endif()
    endforeach()
endfunction()

# Wraps add_subdirectory and moves all created targets to "Import"
function(add_subdirectory_import dir)
    # Save list of existing targets
    get_property(_before_targets GLOBAL PROPERTY TARGETS)

    # Save important context variables
    set(SAVED_CMAKE_FOLDER "${CMAKE_FOLDER}")
    set(SAVED_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    set(SAVED_CURRENT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

    # Set a folder for grouping in IDEs like Visual Studio/Xcode
    set(CMAKE_FOLDER "Import")

    # Add the dependency
    add_subdirectory(${dir} ${ARGN})

    # Restore previous context
    set(CMAKE_FOLDER "${SAVED_CMAKE_FOLDER}")
    set(CMAKE_CURRENT_SOURCE_DIR "${SAVED_CURRENT_SOURCE_DIR}")
    set(CMAKE_CURRENT_BINARY_DIR "${SAVED_CURRENT_BINARY_DIR}")

    # Capture all new targets
    get_property(_after_targets GLOBAL PROPERTY TARGETS)
    list(REMOVE_ITEM _after_targets ${_before_targets})

    # Apply "Import" folder to all new targets
    foreach(target IN LISTS _after_targets)
        if(TARGET ${target})
            set_target_properties(${target} PROPERTIES FOLDER "Import")
        endif()
    endforeach()
endfunction()

# Manually mark a target as part of Import
function(mark_target_import target_name)
    if(TARGET ${target_name})
        set_target_properties(${target_name} PROPERTIES FOLDER "Import")
    endif()
endfunction()

# Mark multiple targets
function(mark_targets_import)
    foreach(name IN LISTS ARGN)
        mark_target_import(${name})
    endforeach()
endfunction()