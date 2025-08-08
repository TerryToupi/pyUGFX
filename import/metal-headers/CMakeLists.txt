cmake_minimum_required(VERSION 3.30) 

project(Metal-Headers) 

add_library(MetalHeaders STATIC) 
add_library(Metal::Headers ALIAS MetalHeaders) 

target_sources(MetalHeaders
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/source/Metal.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Metal.hpp
)

target_include_directories(MetalHeaders
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
)