#ifndef __VULKAN_DEVICE_HPP__
#define __VULKAN_DEVICE_HPP__

#include <device.hpp>
#include <optional>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <vulkanCommon.hpp>

namespace gfx
{
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> computeFamily;
        std::optional<uint32_t> transferFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR Capabilities{};
        std::vector<VkSurfaceFormatKHR> Formats;
        std::vector<VkPresentModeKHR> PresentModes;
    };

	class VulkanDevice final : public Device
	{
    public:
		virtual void Init() override;
		virtual void ShutDown() override;
 
        VkInstance GetInstance();
        VkDevice GetDevice();
        VkPhysicalDevice GetAdapter();
        QueueFamilyIndices GetQueueIndicies();
        
    private:
        void CreateInstance();
        void SetupDebugMessenger();
        void CreateSurface();
        void SelectPhysicalDevice();
        void CreateLogicalDevice();
        
    private:
        bool CheckValidationLayerSupport();
        std::vector<const char*> GetRequiredExtensions();
        bool CheckInstanceExtensionSupport(const std::vector<const char*>& extensionNames);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
        bool IsDeviceSuitable(VkPhysicalDevice device);

        
    private:
        VkInstance m_Instance;
        VkDebugUtilsMessengerEXT m_DebugMessenger;
        VkPhysicalDevice m_PhysicalDevice;
        VkPhysicalDeviceProperties m_VkGPUProperties;
        VkDevice m_Device;
        QueueFamilyIndices m_QueueIndices;

        const std::vector<const char*> m_InstanceExtensions =
        {
            VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME,
            
            #if defined(__APPLE__)
            VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
            VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
            #endif
        };

        const std::vector<const char*> m_DeviceExtensions =
        {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
            VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME,
            VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME,
            VK_KHR_BIND_MEMORY_2_EXTENSION_NAME,
        };

        const std::vector<const char*> m_ValidationLayers =
        {
            "VK_LAYER_KHRONOS_validation"
        };

        #ifdef DEBUG
        const bool m_EnableValidationLayers = true;
        #else
        const bool m_EnableValidationLayers = false;
        #endif
	};
}

#endif
