cmake_minimum_required(VERSION 3.30)

project(pyUGFX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PYUGFX_ENABLE_TESTS "Enabling testing" ON)
option(PYUGFX_ENABLE_VULKAN "Enabling Vulkan platform API" OFF)
option(PYUGFX_ENABLE_METAL "Enabling Metal platform API" OFF)

if(WIN32)
    message(STATUS "Windows detected")
    if(NOT PYUGFX_ENABLE_VULKAN)
        message(STATUS "Enabling Vulkan API!")
        set(PYUGFX_ENABLE_VULKAN ON CACHE BOOL "Enabling Vulkan platform API" FORCE)
    endif()
elseif(APPLE)
    message(STATUS "macOS detected")
    if(NOT PYUGFX_ENABLE_METAL)
        message(STATUS "Enabling Metal API!")
        set(PYUGFX_ENABLE_METAL ON CACHE BOOL "Enabling Metal platform API" FORCE)
    endif()
endif()

# configuring enviroments
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(MSVC)

set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_SOURCE_DIR}/import" CACHE PATH "")
set(CPM_USE_NAMED_CACHE_DIRECTORIES ON)

include(cmake/CPM.cmake)
include(cmake/utils.cmake)

add_subdirectory(import)
add_subdirectory(source)

if(PYUGFX_ENABLE_TESTS)
    add_subdirectory(tests)
endif()