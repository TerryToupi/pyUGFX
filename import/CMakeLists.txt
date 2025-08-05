cmake_minimum_required(VERSION 3.30)
include(FetchContent)

# just so we can use fetchcontent declare and populate together
cmake_policy(SET CMP0169 OLD)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(ImportLibraries)

add_library(${PROJECT_NAME} INTERFACE)

#setting up python for external setup of some libraries
find_package(Python3 REQUIRED COMPONENTS Interpreter)
if (NOT Python3_FOUND)
    message(FATAL_ERROR "Python3 not found! Please install Python3.")
endif()

# Vulkan-Headers
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vulkan-headers")
FetchContent_Declare(
    Vulkan-Headers
    GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
    GIT_TAG vulkan-sdk-1.4.321.0 
)
FetchContent_MakeAvailable(Vulkan-Headers)
mark_target_import(Vulkan-Headers)

# volk
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/volk")
FetchContent_Declare(
    volk
    GIT_REPOSITORY https://github.com/zeux/volk.git
    GIT_TAG vulkan-sdk-1.4.321.0 
)
FetchContent_MakeAvailable(volk)
mark_targets_import(volk)

# VulkanMemoryAllocator
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vma")
FetchContent_Declare(
    VulkanMemoryAllocator
    GIT_REPOSITORY https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git
    GIT_TAG v3.3.0 
)
FetchContent_MakeAvailable(VulkanMemoryAllocator)
mark_targets_import(VulkanMemoryAllocator)

# GLFW
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glfw")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)
mark_targets_import(glfw)

# pybind11
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/pybind")
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v3.0.0
)
FetchContent_MakeAvailable(pybind11)
mark_targets_import(pybind11)

# spdlog
set(SPDLOG_BUILD_TESTS OFF)
set(SPDLOG_BUILD_SHARED OFF)

set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/spdlog")
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.3
)
FetchContent_MakeAvailable(spdlog)
mark_targets_import(spdlog)

# shaderc
set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaderc")
FetchContent_Declare(
    shaderc
    GIT_REPOSITORY https://github.com/google/shaderc.git
    GIT_TAG v2025.1
)
FetchContent_Populate(shaderc)
# Run git-sync-deps BEFORE configuring shaderc
execute_process(
    COMMAND ${Python3_EXECUTABLE} ${shaderc_SOURCE_DIR}/utils/git-sync-deps
    WORKING_DIRECTORY ${shaderc_SOURCE_DIR}
    RESULT_VARIABLE sync_result
)
if(NOT sync_result EQUAL 0)
    message(FATAL_ERROR "Failed to sync shaderc dependencies!")
endif()
#Trying to make available shaderc
add_subdirectory_import(${shaderc_SOURCE_DIR} ${shaderc_BINARY_DIR})

# Connecting dependencies
target_link_libraries(${PROJECT_NAME}
    INTERFACE Vulkan-Headers
    INTERFACE volk
    INTERFACE VulkanMemoryAllocator
    INTERFACE glfw
    INTERFACE pybind11::pybind11
    INTERFACE shaderc
    INTERFACE spdlog::spdlog
)
