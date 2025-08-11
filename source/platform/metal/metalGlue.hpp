#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>
#include <Foundation/Foundation.hpp>
#include <AppKit/AppKit.hpp>

#include <log.hpp>
#include <assert.hpp>

NS::Window* get_ns_window(GLFWwindow* window, CA::MetalLayer* layer);
