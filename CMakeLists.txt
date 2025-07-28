cmake_minimum_required(VERSION 3.30)

project(pyUGFX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# setting additional options
# building/testing/pybind

add_subdirectory(import)
add_subdirectory(source)

# configuring enviroments
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif(MSVC)
