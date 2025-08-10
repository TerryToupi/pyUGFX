#ifndef __vulkan_common_hpp__
#define __vulkan_common_hpp__

#define VK_ENABLE_BETA_EXTENSIONS
#include <volk.h>

#include <log.hpp>
#include <assert.hpp>

inline void VK_CHECK(VkResult r, const char* context = "") {
    GFX_ASSERT(r == VK_SUCCESS, std::string("[Vulkan ERROR] ") + std::to_string(r) + " " + context);
}

#endif
