cmake_minimum_required(VERSION 3.30)

project(pyUGFX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
add_subdirectory(tests)