cmake_minimum_required(VERSION 3.30)

project(ImportLibraries)

add_library(${PROJECT_NAME} INTERFACE)

#setting up python for external setup of some libraries
find_package(Python3 REQUIRED COMPONENTS Interpreter)
if (NOT Python3_FOUND)
    message(FATAL_ERROR "Python3 not found! Please install Python3.")
endif()


#############################
#   UNIVERSAL DEPENDECIES   #
#############################

CPMAddPackage(
    NAME glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

CPMAddPackage(
    NAME pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v3.0.0
)

CPMAddPackage(
    NAME spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.15.3
)

CPMAddPackage(
    NAME spirv-headers
    GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Headers.git
    GIT_TAG main 
)

# 2. Fetch spirv-tools
CPMAddPackage(
    NAME spirv-tools
    GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Tools.git
    GIT_TAG main 
)

# 3. Fetch glslang
CPMAddPackage(
    NAME glslang
    GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
    GIT_TAG main
)

set(SHADERC_SKIP_TESTS ON CACHE BOOL "Skip shaderc tests" FORCE)
set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "Skip shaderc examples" FORCE)
CPMAddPackage(
    NAME shaderc
    GITHUB_REPOSITORY google/shaderc
    GIT_TAG main
)

# Connecting dependencies
target_link_libraries(${PROJECT_NAME}
    INTERFACE glfw
    INTERFACE pybind11::pybind11
    INTERFACE shaderc
    INTERFACE spdlog::spdlog
)

#####################################
#   PLATFROM SPACIFIC DEPENDECIES   #
#####################################

####################
# PLATFORM VULLKAN #
####################

if(PYUGFX_ENABLE_VULKAN)
    CPMAddPackage(
        NAME Vulkan-Headers
        GIT_REPOSITORY https://github.com/KhronosGroup/Vulkan-Headers.git
        GIT_TAG vulkan-sdk-1.4.321.0
    )

    CPMAddPackage(
        NAME volk
        GIT_REPOSITORY https://github.com/zeux/volk.git
        GIT_TAG vulkan-sdk-1.4.321.0 
    )

    CPMAddPackage(
        NAME VulkanMemoryAllocator
        GIT_REPOSITORY https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git
        GIT_TAG v3.3.0 
    )

    target_link_libraries(${PROJECT_NAME}
        INTERFACE Vulkan-Headers 
        INTERFACE volk 
        INTERFACE GPUOpen::VulkanMemoryAllocator
    )
endif()

##################
# PLATFORM Metal #
##################

if(PYUGFX_ENABLE_METAL)
    CPMAddPackage(
        Name Metal-Headers
        GIT_REPOSITORY https://github.com/TerryToupi/Metal-Headers.git
        GIT_TAG main
    )

    target_link_libraries(${PROJECT_NAME} 
        INTERFACE Metal::Headers
    )

    find_library(METAL Metal) 
    find_library(FOUNDATION Foundation)
    find_library(QUARTZCORE QuartzCore)
    find_library(APPKIT AppKit)

    target_link_libraries(${PROJECT_NAME}
        INTERFACE stdc++
        INTERFACE "-framework Metal"
        INTERFACE "-framework Foundation"
        INTERFACE "-framework QuartzCore"
        INTERFACE "-framework AppKit"
        INTERFACE objc
    )
endif()
