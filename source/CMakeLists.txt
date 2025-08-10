cmake_minimum_required(VERSION 3.30)

project(pyUGFX_library)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# publicly included headers
file(GLOB_RECURSE CONTEXT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/context/**.hpp")
file(GLOB_RECURSE RHI_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/RHI/**.hpp")
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/**.hpp")

# platform spacific files
file(GLOB_RECURSE CONTEXT_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/platform/context/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/platform/context/**.cpp")
file(GLOB_RECURSE METAL_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/platform/metal/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/platform/metal/**.cpp")
file(GLOB_RECURSE VULKAN_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/platform/vulkan/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/platform/vulkan/**.cpp")

add_library(pyUGFX_library STATIC)
add_library(pyUGFX::library ALIAS pyUGFX_library)

target_sources(pyUGFX_library
    PRIVATE ${CONTEXT_HEADERS}
    PRIVATE ${RHI_HEADERS}
    PRIVATE ${UTILS_HEADERS}
)
target_include_directories(pyUGFX_library
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/RHI/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/utils/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/context/"
)
group_sources_by_folder_from_list(CONTEXT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(RHI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(UTILS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")

# including Context source files
target_sources(pyUGFX_library
    PRIVATE ${CONTEXT_FILES}
)
target_include_directories(pyUGFX_library
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/platform/context/"
)
group_sources_by_folder_from_list(CONTEXT_FILES "${CMAKE_CURRENT_SOURCE_DIR}")

# vulkan specific platform files
if(PYUGFX_ENABLE_VULKAN)
    target_sources(pyUGFX_library
        PRIVATE ${VULKAN_FILES}
    )
    target_include_directories(pyUGFX_library
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/platform/vulkan/"
    )
    group_sources_by_folder_from_list(VULKAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# metal specific platform files
if(PYUGFX_ENABLE_METAL)
    target_sources(pyUGFX_library
        PRIVATE ${METAL_FILES}
    )
    target_include_directories(pyUGFX_library
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/platform/metal/"
    )
    group_sources_by_folder_from_list(METAL_FILES "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# platform definitions
target_compile_definitions(pyUGFX_library
    PUBLIC PYUGFX_ENABLE_VULKAN=$<BOOL:${PYUGFX_ENABLE_VULKAN}>
    PUBLIC PYUGFX_ENABLE_METAL=$<BOOL:${PYUGFX_ENABLE_METAL}>
)

target_link_libraries(pyUGFX_library
    PRIVATE ImportLibraries
)
