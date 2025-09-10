/// \cond

#ifndef __VULKAN_DEVICE_HPP__
#define __VULKAN_DEVICE_HPP__

#include <log.hpp>
#include <assert.hpp>
#include <device.hpp>
#include <vulkanCommon.hpp>

namespace gfx
{
	struct QueueInfo
	{
		uint32_t familyIndex = ~0U;  // Family index of the queue (graphic, compute, transfer, ...)
		uint32_t queueIndex = ~0U;  // Index of the queue in the family
		VkQueue  queue{};            // The queue object
	};

	class VulkanDevice final : public Device
	{
    public:
		VulkanDevice() = default;
		~VulkanDevice() { ASSERT(m_device == VK_NULL_HANDLE, "Missing ShutDown(()!"); }

		virtual void Init() override;
		virtual void ShutDown() override;

		void initInstance();
		void selectPhysicalDevice();
		void initLogicalDevice();

		VkDevice         getDevice() const { return m_device; }
		VkPhysicalDevice getPhysicalDevice() const { return m_physicalDevice; }
		VkInstance       getInstance() const { return m_instance; }
		const QueueInfo& getGraphicsQueue() const { return m_queues[0]; }
		uint32_t         getApiVersion() const { return m_apiVersion; }

		VkPhysicalDeviceFeatures2                        getPhysicalDeviceFeatures() const { return m_deviceFeatures; }
		VkPhysicalDeviceVulkan11Features                 getVulkan11Features() const { return m_features11; }
		VkPhysicalDeviceVulkan12Features                 getVulkan12Features() const { return m_features12; }
		VkPhysicalDeviceVulkan13Features                 getVulkan13Features() const { return m_features13; }
		VkPhysicalDeviceVulkan14Features                 getVulkan14Features() const { return m_features14; }
		VkPhysicalDeviceExtendedDynamicStateFeaturesEXT  getDynamicStateFeatures() const { return m_dynamicStateFeatures; }
		VkPhysicalDeviceExtendedDynamicState2FeaturesEXT getDynamicState2Features() const { return m_dynamicState2Features; }
		VkPhysicalDeviceExtendedDynamicState3FeaturesEXT getDynamicState3Features() const { return m_dynamicState3Features; }
		VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT getSwapchainFeatures() const { return m_swapchainFeatures; }

	private:
		void getAvailableInstanceExtensions();
		void getAvailableDeviceExtensions();
		bool extensionIsAvailable(const std::string& name, const std::vector<VkExtensionProperties>& extensions);
		QueueInfo getQueue(VkQueueFlagBits flags) const;

    private:
		// --- Members ------------------------------------------------------------------------------------------------------------
		uint32_t m_apiVersion{ 0 };  // The Vulkan API version

		// Instance extension, extra extensions can be added here
		std::vector<const char*> m_instanceExtensions = { 
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME,
			VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME
		};
		std::vector<const char*> m_instanceLayers = {};  // Add extra layers here

		// Device features, extra features can be added here
		VkPhysicalDeviceFeatures2        m_deviceFeatures{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2 };
		VkPhysicalDeviceVulkan11Features m_features11{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES };
		VkPhysicalDeviceVulkan12Features m_features12{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };
		VkPhysicalDeviceVulkan13Features m_features13{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };
		VkPhysicalDeviceVulkan14Features m_features14{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES };
		VkPhysicalDeviceSwapchainMaintenance1FeaturesEXT m_swapchainFeatures{
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SWAPCHAIN_MAINTENANCE_1_FEATURES_EXT };
		VkPhysicalDeviceExtendedDynamicStateFeaturesEXT m_dynamicStateFeatures{
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_FEATURES_EXT };
		VkPhysicalDeviceExtendedDynamicState2FeaturesEXT m_dynamicState2Features{
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_2_FEATURES_EXT };
		VkPhysicalDeviceExtendedDynamicState3FeaturesEXT m_dynamicState3Features{
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTENDED_DYNAMIC_STATE_3_FEATURES_EXT };

		// Properties: how much a feature can do
		VkPhysicalDevicePushDescriptorPropertiesKHR m_pushDescriptorProperties{
			.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PUSH_DESCRIPTOR_PROPERTIES_KHR };

		std::vector<VkBaseOutStructure*> m_linkedDeviceProperties{ 
			reinterpret_cast<VkBaseOutStructure*>(&m_pushDescriptorProperties) };

		// Device extension, extra extensions can be added here
		std::vector<const char*> m_deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,  // Needed for display on the screen
		};

		VkInstance                         m_instance{};        // The Vulkan instance
		VkPhysicalDevice                   m_physicalDevice{};  // The physical device (GPU)
		VkDevice                           m_device{};          // The logical device (interface to the physical device)
		std::vector<QueueInfo>             m_queues{};          // The queue used to submit command buffers to the GPU
		VkDebugUtilsMessengerEXT           m_callback{ VK_NULL_HANDLE };  // The debug callback
		std::vector<VkExtensionProperties> m_instanceExtensionsAvailable{};
		std::vector<VkExtensionProperties> m_deviceExtensionsAvailable{};
#ifdef NDEBUG
		bool m_enableValidationLayers = false;
#else
		bool m_enableValidationLayers = true;
#endif	
	};
}

#endif

/// \endcond
