project(pyUGFX_library)

file(GLOB_RECURSE RHI_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/RHI/**.hpp")
file(GLOB_RECURSE UTILS_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/utils/**.hpp")

add_library(pyUGFX_library STATIC)
add_library(pyUGFX::lib ALIAS pyUGFX_library)

target_sources(pyUGFX_library
    PRIVATE ${RHI_HEADERS}
    PRIVATE ${UTILS_HEADERS}
)

target_include_directories(pyUGFX_library
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/RHI/"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/utils/"
)

target_link_libraries(pyUGFX_library
    PRIVATE ImportLibraries
)