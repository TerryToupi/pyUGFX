/// \cond

#ifndef __vulkan_common_hpp__
#define __vulkan_common_hpp__

#define VK_ENABLE_BETA_EXTENSIONS
#include <volk.h>
#include <vma.hpp>

#include <string>
#include <log.hpp>
#include <assert.hpp>

#ifdef NDEBUG
static inline const char* string_VkResult(VkResult input_value) {
    return "Unhandled VkResult";
}
#else
static inline const char* string_VkResult(VkResult input_value) {
    switch (input_value) {
    case VK_SUCCESS:
        return "VK_SUCCESS";
    case VK_NOT_READY:
        return "VK_NOT_READY";
    case VK_TIMEOUT:
        return "VK_TIMEOUT";
    case VK_EVENT_SET:
        return "VK_EVENT_SET";
    case VK_EVENT_RESET:
        return "VK_EVENT_RESET";
    case VK_INCOMPLETE:
        return "VK_INCOMPLETE";
    case VK_ERROR_OUT_OF_HOST_MEMORY:
        return "VK_ERROR_OUT_OF_HOST_MEMORY";
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
    case VK_ERROR_INITIALIZATION_FAILED:
        return "VK_ERROR_INITIALIZATION_FAILED";
    case VK_ERROR_DEVICE_LOST:
        return "VK_ERROR_DEVICE_LOST";
    case VK_ERROR_MEMORY_MAP_FAILED:
        return "VK_ERROR_MEMORY_MAP_FAILED";
    case VK_ERROR_LAYER_NOT_PRESENT:
        return "VK_ERROR_LAYER_NOT_PRESENT";
    case VK_ERROR_EXTENSION_NOT_PRESENT:
        return "VK_ERROR_EXTENSION_NOT_PRESENT";
    case VK_ERROR_FEATURE_NOT_PRESENT:
        return "VK_ERROR_FEATURE_NOT_PRESENT";
    case VK_ERROR_INCOMPATIBLE_DRIVER:
        return "VK_ERROR_INCOMPATIBLE_DRIVER";
    case VK_ERROR_TOO_MANY_OBJECTS:
        return "VK_ERROR_TOO_MANY_OBJECTS";
    case VK_ERROR_FORMAT_NOT_SUPPORTED:
        return "VK_ERROR_FORMAT_NOT_SUPPORTED";
    case VK_ERROR_FRAGMENTED_POOL:
        return "VK_ERROR_FRAGMENTED_POOL";
    case VK_ERROR_UNKNOWN:
        return "VK_ERROR_UNKNOWN";
    case VK_ERROR_OUT_OF_POOL_MEMORY:
        return "VK_ERROR_OUT_OF_POOL_MEMORY";
    case VK_ERROR_INVALID_EXTERNAL_HANDLE:
        return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
    case VK_ERROR_FRAGMENTATION:
        return "VK_ERROR_FRAGMENTATION";
    case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:
        return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
    case VK_PIPELINE_COMPILE_REQUIRED:
        return "VK_PIPELINE_COMPILE_REQUIRED";
    case VK_ERROR_NOT_PERMITTED:
        return "VK_ERROR_NOT_PERMITTED";
    case VK_ERROR_SURFACE_LOST_KHR:
        return "VK_ERROR_SURFACE_LOST_KHR";
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
    case VK_SUBOPTIMAL_KHR:
        return "VK_SUBOPTIMAL_KHR";
    case VK_ERROR_OUT_OF_DATE_KHR:
        return "VK_ERROR_OUT_OF_DATE_KHR";
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
    case VK_ERROR_VALIDATION_FAILED_EXT:
        return "VK_ERROR_VALIDATION_FAILED_EXT";
    case VK_ERROR_INVALID_SHADER_NV:
        return "VK_ERROR_INVALID_SHADER_NV";
    case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR:
        return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR:
        return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR:
        return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:
        return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR:
        return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
    case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR:
        return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
    case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:
        return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
    case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:
        return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
    case VK_THREAD_IDLE_KHR:
        return "VK_THREAD_IDLE_KHR";
    case VK_THREAD_DONE_KHR:
        return "VK_THREAD_DONE_KHR";
    case VK_OPERATION_DEFERRED_KHR:
        return "VK_OPERATION_DEFERRED_KHR";
    case VK_OPERATION_NOT_DEFERRED_KHR:
        return "VK_OPERATION_NOT_DEFERRED_KHR";
    case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR:
        return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
    case VK_ERROR_COMPRESSION_EXHAUSTED_EXT:
        return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
    case VK_INCOMPATIBLE_SHADER_BINARY_EXT:
        return "VK_INCOMPATIBLE_SHADER_BINARY_EXT";
    case VK_PIPELINE_BINARY_MISSING_KHR:
        return "VK_PIPELINE_BINARY_MISSING_KHR";
    case VK_ERROR_NOT_ENOUGH_SPACE_KHR:
        return "VK_ERROR_NOT_ENOUGH_SPACE_KHR";
    default:
        return "Unhandled VkResult";
    }
}
#endif

#ifdef NDEBUG
#define VK_CHECK(vkFnc) vkFnc
#else
#define VK_CHECK(vkFnc)                                                                                                \
  {                                                                                                                    \
    if(const VkResult checkResult = (vkFnc); checkResult != VK_SUCCESS)                                                \
    {                                                                                                                  \
      const char* errMsg = string_VkResult(checkResult);                                                               \
      LOGE("Vulkan error: %s", errMsg);                                                                                \
      ASSERT(checkResult == VK_SUCCESS, errMsg);                                                                       \
    }                                                                                                                  \
  }
#endif

// ------------------- vk_minimal_laters - dubug_utils.h ------------------------

/*
 * Copyright (c) 2023-2024, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-FileCopyrightText: Copyright (c) 2023-2024, NVIDIA CORPORATION.
 * SPDX-License-Identifier: Apache-2.0
 */

 // This file defines the DebugUtil class, a singleton utility for managing Vulkan debug utilities.
 // It provides functionality to set debug names for Vulkan objects and manage debug labels in command buffers.
 //
 // Usage:
 // 1. Initialize the DebugUtil with a Vulkan device using debugUtilInitialize(VkDevice device).
 // 2. Use DBG_VK_NAME(obj) macro to set debug names for Vulkan objects.
 // 3. Use DBG_VK_SCOPE(cmdBuf) macro to create scoped debug labels in command buffers.
 //
 // Example:
 // debugUtilInitialize(device);
 // VkBuffer buffer = createBufer(...)
 // DBG_VK_NAME(buffer);
 //
 // void someFunction(VkCommandBuffer cmdBuf)
 // {
 //   DBG_VK_SCOPE(cmdBuf);
 //   // Command buffer operations
 // }

#include <type_traits>  // std::is_same_v
#include <cstring>      // for strrchr
#include <string>

namespace utils {

    class DebugUtil
    {
    public:
        static DebugUtil& getInstance()
        {
            static DebugUtil instance;
            return instance;
        }

        void init(VkDevice device) { m_device = device; }

        bool isInitialized() const { return m_device != VK_NULL_HANDLE; }

        template <typename T>
        void setObjectName(T object, const std::string& name) const;

        class ScopedCmdLabel
        {
        public:
            ScopedCmdLabel(VkCommandBuffer cmdBuf, const std::string& label)
                : m_cmdBuf(cmdBuf)
            {
                if (vkCmdBeginDebugUtilsLabelEXT != nullptr)
                {
                    VkDebugUtilsLabelEXT s{ VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT, nullptr, label.c_str(), {1.0f, 1.0f, 1.0f, 1.0f} };
                    vkCmdBeginDebugUtilsLabelEXT(m_cmdBuf, &s);
                }
            }

            ~ScopedCmdLabel()
            {
                if (vkCmdEndDebugUtilsLabelEXT != nullptr)
                    vkCmdEndDebugUtilsLabelEXT(m_cmdBuf);
            }

        private:
            VkCommandBuffer m_cmdBuf;
        };

    private:
        DebugUtil() = default;
        VkDevice m_device{ VK_NULL_HANDLE };

        template <typename T>
        static constexpr VkObjectType getObjectType();
    };

    template <typename T>
    void DebugUtil::setObjectName(T object, const std::string& name) const
    {
        constexpr VkObjectType objectType = getObjectType<T>();

        if (vkSetDebugUtilsObjectNameEXT != nullptr && objectType != VK_OBJECT_TYPE_UNKNOWN && m_device != VK_NULL_HANDLE)
        {
            VkDebugUtilsObjectNameInfoEXT s{ VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT, nullptr, objectType,
                                            (uint64_t)object, name.c_str() };
            vkSetDebugUtilsObjectNameEXT(m_device, &s);
        }
    }

    template <typename T>
    constexpr VkObjectType DebugUtil::getObjectType()
    {
        if constexpr (std::is_same_v<T, VkBuffer>)
            return VK_OBJECT_TYPE_BUFFER;
        else if constexpr (std::is_same_v<T, VkBufferView>)
            return VK_OBJECT_TYPE_BUFFER_VIEW;
        else if constexpr (std::is_same_v<T, VkCommandBuffer>)
            return VK_OBJECT_TYPE_COMMAND_BUFFER;
        else if constexpr (std::is_same_v<T, VkCommandPool>)
            return VK_OBJECT_TYPE_COMMAND_POOL;
        else if constexpr (std::is_same_v<T, VkDescriptorPool>)
            return VK_OBJECT_TYPE_DESCRIPTOR_POOL;
        else if constexpr (std::is_same_v<T, VkDescriptorSet>)
            return VK_OBJECT_TYPE_DESCRIPTOR_SET;
        else if constexpr (std::is_same_v<T, VkDescriptorSetLayout>)
            return VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT;
        else if constexpr (std::is_same_v<T, VkDevice>)
            return VK_OBJECT_TYPE_DEVICE;
        else if constexpr (std::is_same_v<T, VkDeviceMemory>)
            return VK_OBJECT_TYPE_DEVICE_MEMORY;
        else if constexpr (std::is_same_v<T, VkFence>)
            return VK_OBJECT_TYPE_FENCE;
        else if constexpr (std::is_same_v<T, VkFramebuffer>)
            return VK_OBJECT_TYPE_FRAMEBUFFER;
        else if constexpr (std::is_same_v<T, VkImage>)
            return VK_OBJECT_TYPE_IMAGE;
        else if constexpr (std::is_same_v<T, VkImageView>)
            return VK_OBJECT_TYPE_IMAGE_VIEW;
        else if constexpr (std::is_same_v<T, VkInstance>)
            return VK_OBJECT_TYPE_INSTANCE;
        else if constexpr (std::is_same_v<T, VkPipeline>)
            return VK_OBJECT_TYPE_PIPELINE;
        else if constexpr (std::is_same_v<T, VkPipelineCache>)
            return VK_OBJECT_TYPE_PIPELINE_CACHE;
        else if constexpr (std::is_same_v<T, VkPipelineLayout>)
            return VK_OBJECT_TYPE_PIPELINE_LAYOUT;
        else if constexpr (std::is_same_v<T, VkQueryPool>)
            return VK_OBJECT_TYPE_QUERY_POOL;
        else if constexpr (std::is_same_v<T, VkRenderPass>)
            return VK_OBJECT_TYPE_RENDER_PASS;
        else if constexpr (std::is_same_v<T, VkSampler>)
            return VK_OBJECT_TYPE_SAMPLER;
        else if constexpr (std::is_same_v<T, VkSemaphore>)
            return VK_OBJECT_TYPE_SEMAPHORE;
        else if constexpr (std::is_same_v<T, VkShaderModule>)
            return VK_OBJECT_TYPE_SHADER_MODULE;
        else if constexpr (std::is_same_v<T, VkSurfaceKHR>)
            return VK_OBJECT_TYPE_SURFACE_KHR;
        else if constexpr (std::is_same_v<T, VkSwapchainKHR>)
            return VK_OBJECT_TYPE_SWAPCHAIN_KHR;
        else
            return VK_OBJECT_TYPE_UNKNOWN;
    }
}  // namespace utils

#define DBG_VK_SCOPE(_cmd) utils::DebugUtil::ScopedCmdLabel scopedCmdLabel(_cmd, __FUNCTION__)

#define DBG_VK_NAME(obj)                                                                                                       \
  if(utils::DebugUtil::getInstance().isInitialized())                                                                          \
  utils::DebugUtil::getInstance().setObjectName(                                                                               \
      obj, std::string(std::max(std::max(typeid(*this).name(), strrchr(typeid(*this).name(), ' ') + 1), typeid(*this).name())) \
               + "::" + #obj + " (" + std::string(" in ")                                                                      \
               + std::max({__FILE__, strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__,                         \
                           strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__})                                    \
               + ":" + std::to_string(__LINE__) + ")")


inline void debugUtilInitialize(VkDevice device)
{
    utils::DebugUtil::getInstance().init(device);
}

#endif

/// \endcond
