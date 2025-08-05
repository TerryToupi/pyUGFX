project(pyUGFX_library)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE CONTEXT_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/context/**.hpp")
file(GLOB_RECURSE RHI_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/RHI/**.hpp")
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/**.hpp")
file(GLOB_RECURSE PLATFORM_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/platform/**.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/platform/**.cpp")

add_library(pyUGFX_library STATIC)
add_library(pyUGFX::lib ALIAS pyUGFX_library)

target_sources(pyUGFX_library
    PRIVATE ${CONTEXT_HEADERS}
    PRIVATE ${RHI_HEADERS}
    PRIVATE ${UTILS_HEADERS}
    PRIVATE ${PLATFORM_FILES}
)

target_include_directories(pyUGFX_library
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/RHI/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/utils/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/context/"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/platform/"
)

target_link_libraries(pyUGFX_library
    PRIVATE ImportLibraries
)

group_sources_by_folder_from_list(CONTEXT_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(RHI_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(UTILS_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
group_sources_by_folder_from_list(PLATFORM_FILES "${CMAKE_CURRENT_SOURCE_DIR}")