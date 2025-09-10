cmake_minimum_required(VERSION 3.30)

project(pyUGFX_library)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# publicly included headers
file(GLOB_RECURSE CORE_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/core/**.hpp")
file(GLOB_RECURSE RHI_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/RHI/**.hpp")
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/**.hpp")

# platform spacific files
file(GLOB_RECURSE CORE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/backend/core/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/backend/core/**.cpp")
file(GLOB_RECURSE METAL_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/backend/metal/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/backend/metal/**.cpp")
file(GLOB_RECURSE METAL_OBJC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/backend/metal/**.mm")
file(GLOB_RECURSE VULKAN_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/backend/vulkan/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/backend/vulkan/**.cpp")

add_library(pyUGFX_library STATIC)
add_library(pyUGFX::library ALIAS pyUGFX_library)

target_sources(pyUGFX_library
    PRIVATE ${CORE_HEADERS}
    PRIVATE ${RHI_HEADERS}
    PRIVATE ${UTILS_HEADERS}
)
target_include_directories(pyUGFX_library
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/RHI/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/utils/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/core/"
)
group_sources_by_folder_from_list(CORE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(RHI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(UTILS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")

# including Context source files
target_sources(pyUGFX_library
    PRIVATE ${CORE_FILES}
)
target_include_directories(pyUGFX_library
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/backend/core/"
)
group_sources_by_folder_from_list(CORE_FILES "${CMAKE_CURRENT_SOURCE_DIR}")

# vulkan specific platform files
if(PYUGFX_ENABLE_VULKAN)
    target_sources(pyUGFX_library
        PRIVATE ${VULKAN_FILES}
    )
    target_include_directories(pyUGFX_library
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/backend/vulkan/"
    )
    group_sources_by_folder_from_list(VULKAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# metal specific platform files
if(PYUGFX_ENABLE_METAL)
    target_sources(pyUGFX_library
        PRIVATE ${METAL_FILES}
        PRIVATE ${METAL_OBJC_FILES}
    )
    # set_source_files_properties(${METAL_OBJC_FILES}
    #     PROPERTIES LANGUAGE OBJCXX
    # )
    target_include_directories(pyUGFX_library
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/backend/metal/"
    )
    group_sources_by_folder_from_list(METAL_FILES "${CMAKE_CURRENT_SOURCE_DIR}")
    group_sources_by_folder_from_list(METAL_OBJC_FILES "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# platform definitions
target_compile_definitions(pyUGFX_library
    PUBLIC 
        PYUGFX_ENABLE_VULKAN=$<BOOL:${PYUGFX_ENABLE_VULKAN}>
        PYUGFX_ENABLE_METAL=$<BOOL:${PYUGFX_ENABLE_METAL}>
)

target_compile_definitions(pyUGFX_library 
    PUBLIC
        $<$<CONFIG:Debug>:DEBUG=1>
        $<$<NOT:$<CONFIG:Debug>>:DEBUG=0>
)

target_link_libraries(pyUGFX_library
    PRIVATE ImportLibraries
)

if(${CMAKE_GENERATOR} MATCHES "Xcode")
    set_target_properties(pyUGFX_library
        PROPERTIES 
            XCODE_GENERATE_SCHEME TRUE
            XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    )
endif()