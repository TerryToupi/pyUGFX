#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>

// Helper to chain elements to the pNext
template <typename MainT, typename NewT>
static void pNextChainPushFront(MainT* mainStruct, NewT* newStruct)
{
    newStruct->pNext = mainStruct->pNext;
    mainStruct->pNext = newStruct;
}

// Validation settings: to fine tune what is checked
struct ValidationSettings
{
    VkBool32 fine_grained_locking{ VK_TRUE };
    VkBool32 validate_core{ VK_TRUE };
    VkBool32 check_image_layout{ VK_TRUE };
    VkBool32 check_command_buffer{ VK_TRUE };
    VkBool32 check_object_in_use{ VK_TRUE };
    VkBool32 check_query{ VK_TRUE };
    VkBool32 check_shaders{ VK_TRUE };
    VkBool32 check_shaders_caching{ VK_TRUE };
    VkBool32 unique_handles{ VK_TRUE };
    VkBool32 object_lifetime{ VK_TRUE };
    VkBool32 stateless_param{ VK_TRUE };
    std::vector<const char*> debug_action{ "VK_DBG_LAYER_ACTION_LOG_MSG" };  // "VK_DBG_LAYER_ACTION_DEBUG_OUTPUT", "VK_DBG_LAYER_ACTION_BREAK"
    std::vector<const char*> report_flags{ "error" };

    VkBaseInStructure* buildPNextChain()
    {
        layerSettings = std::vector<VkLayerSettingEXT>{
            {layerName, "fine_grained_locking", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &fine_grained_locking},
            {layerName, "validate_core", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &validate_core},
            {layerName, "check_image_layout", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &check_image_layout},
            {layerName, "check_command_buffer", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &check_command_buffer},
            {layerName, "check_object_in_use", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &check_object_in_use},
            {layerName, "check_query", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &check_query},
            {layerName, "check_shaders", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &check_shaders},
            {layerName, "check_shaders_caching", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &check_shaders_caching},
            {layerName, "unique_handles", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &unique_handles},
            {layerName, "object_lifetime", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &object_lifetime},
            {layerName, "stateless_param", VK_LAYER_SETTING_TYPE_BOOL32_EXT, 1, &stateless_param},
            {layerName, "debug_action", VK_LAYER_SETTING_TYPE_STRING_EXT, uint32_t(debug_action.size()), debug_action.data()},
            {layerName, "report_flags", VK_LAYER_SETTING_TYPE_STRING_EXT, uint32_t(report_flags.size()), report_flags.data()},

        };
        layerSettingsCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT,
            .settingCount = uint32_t(layerSettings.size()),
            .pSettings = layerSettings.data(),
        };

        return reinterpret_cast<VkBaseInStructure*>(&layerSettingsCreateInfo);
    }

    static constexpr const char* layerName{ "VK_LAYER_KHRONOS_validation" };
    std::vector<VkLayerSettingEXT> layerSettings{};
    VkLayerSettingsCreateInfoEXT   layerSettingsCreateInfo{};
};

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
    void*)
{
    const utils::Logger::LogLevel level =
        (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) != 0 ? utils::Logger::LogLevel::eERROR :
        (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) != 0 ? utils::Logger::LogLevel::eWARNING :
        utils::Logger::LogLevel::eINFO;
    utils::Logger::getInstance().log(level, "%s", callbackData->pMessage);
    if ((severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) != 0)
    {
#if defined(_MSVC_LANG)
        __debugbreak();
#elif defined(__linux__)
        raise(SIGTRAP);
#elif defined(__llvm__)
        __builtin_trap();
#endif
    }
    return VK_FALSE;
}

void gfx::VulkanDevice::Init()
{
    // initilize the meta loader
    VK_CHECK(volkInitialize());

	initInstance();
	selectPhysicalDevice();
	initLogicalDevice();
}

void gfx::VulkanDevice::ShutDown()
{
	vkDeviceWaitIdle(m_device);
    if (m_enableValidationLayers && vkDestroyDebugUtilsMessengerEXT)
    {
        vkDestroyDebugUtilsMessengerEXT(m_instance, m_callback, nullptr);
    }
    vkDestroyDevice(m_device, nullptr);
    vkDestroyInstance(m_instance, nullptr);
    *this = {};
}

void gfx::VulkanDevice::initInstance()
{
    vkEnumerateInstanceVersion(&m_apiVersion);
    LOGI("VULKAN API: %d.%d", VK_VERSION_MAJOR(m_apiVersion), VK_VERSION_MINOR(m_apiVersion));
    ASSERT(m_apiVersion >= VK_MAKE_API_VERSION(0, 1, 4, 0), "Require Vulkan 1.4 loader");

    // This finds the KHR surface extensions needed to display on the right platform
    uint32_t     glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    getAvailableInstanceExtensions();

    const VkApplicationInfo applicationInfo{
        .pApplicationName = "pyUGFX",
        .applicationVersion = 1,
        .pEngineName = "pyUGFX",
        .engineVersion = 1,
        .apiVersion = m_apiVersion,
    };

    // Add extensions requested by GLFW
    m_instanceExtensions.insert(m_instanceExtensions.end(), glfwExtensions, glfwExtensions + glfwExtensionCount);
    if (extensionIsAvailable(VK_EXT_DEBUG_UTILS_EXTENSION_NAME, m_instanceExtensionsAvailable))
        m_instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);  // Allow debug utils (naming objects)
    if (extensionIsAvailable(VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME, m_instanceExtensionsAvailable))
        m_instanceExtensions.push_back(VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME);

    // Adding the validation layer
    if (m_enableValidationLayers)
    {
        m_instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
    }

    // Setting for the validation layer
    ValidationSettings validationSettings{ .validate_core = VK_TRUE };  // modify default value

    const VkInstanceCreateInfo instanceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pNext = validationSettings.buildPNextChain(),
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = uint32_t(m_instanceLayers.size()),
        .ppEnabledLayerNames = m_instanceLayers.data(),
        .enabledExtensionCount = uint32_t(m_instanceExtensions.size()),
        .ppEnabledExtensionNames = m_instanceExtensions.data(),
    };

    // Actual Vulkan instance creation
    VK_CHECK(vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance));

    // Load all Vulkan functions
    volkLoadInstance(m_instance);

    // Add the debug callback
    if (m_enableValidationLayers && vkCreateDebugUtilsMessengerEXT)
    {
        const VkDebugUtilsMessengerCreateInfoEXT dbg_messenger_create_info{
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
            .pfnUserCallback = debugCallback,  // <-- The callback function
        };
        VK_CHECK(vkCreateDebugUtilsMessengerEXT(m_instance, &dbg_messenger_create_info, nullptr, &m_callback));
        LOGI("Validation Layers: ON");
    }
}

void gfx::VulkanDevice::selectPhysicalDevice()
{
    size_t chosenDevice = 0;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
    ASSERT(deviceCount != 0, "failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, physicalDevices.data());

    VkPhysicalDeviceProperties2 properties2{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
    for (size_t i = 0; i < physicalDevices.size(); i++)
    {
        vkGetPhysicalDeviceProperties2(physicalDevices[i], &properties2);
        if (properties2.properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            chosenDevice = i;
            break;
        }
    }

    m_physicalDevice = physicalDevices[chosenDevice];
    vkGetPhysicalDeviceProperties2(m_physicalDevice, &properties2);
    LOGI("Selected GPU: %s", properties2.properties.deviceName);  // Show the name of the GPU
    LOGI("Driver: %d.%d.%d", VK_VERSION_MAJOR(properties2.properties.driverVersion),
        VK_VERSION_MINOR(properties2.properties.driverVersion), VK_VERSION_PATCH(properties2.properties.driverVersion));
    LOGI("Vulkan API: %d.%d.%d", VK_VERSION_MAJOR(properties2.properties.apiVersion),
        VK_VERSION_MINOR(properties2.properties.apiVersion), VK_VERSION_PATCH(properties2.properties.apiVersion));
}

void gfx::VulkanDevice::initLogicalDevice()
{
    const float queuePriority = 1.0F;
    m_queues.clear();
    m_queues.emplace_back(getQueue(VK_QUEUE_GRAPHICS_BIT));

    // Request only one queue : graphic
    // User could request more specific queues: compute, transfer
    const VkDeviceQueueCreateInfo queueCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = m_queues[0].familyIndex,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority,
    };

    // Chaining all features up to Vulkan 1.4
    pNextChainPushFront(&m_features11, &m_features12);
    pNextChainPushFront(&m_features11, &m_features13);
    pNextChainPushFront(&m_features11, &m_features14);

    /*--
     * Check if the device supports the required extensions
     * Because we cannot request a device with extension it is not supporting
    -*/
    getAvailableDeviceExtensions();
    if (extensionIsAvailable(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME, m_deviceExtensionsAvailable))
    {
        m_deviceExtensions.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);
    }
    if (extensionIsAvailable(VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME, m_deviceExtensionsAvailable))
    {
        pNextChainPushFront(&m_features11, &m_dynamicStateFeatures);
        m_deviceExtensions.push_back(VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME);
    }
    if (extensionIsAvailable(VK_EXT_EXTENDED_DYNAMIC_STATE_2_EXTENSION_NAME, m_deviceExtensionsAvailable))
    {
        pNextChainPushFront(&m_features11, &m_dynamicState2Features);
        m_deviceExtensions.push_back(VK_EXT_EXTENDED_DYNAMIC_STATE_2_EXTENSION_NAME);
    }
    if (extensionIsAvailable(VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME, m_deviceExtensionsAvailable))
    {
        pNextChainPushFront(&m_features11, &m_dynamicState3Features);
        m_deviceExtensions.push_back(VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME);
    }
    if (extensionIsAvailable(VK_EXT_SWAPCHAIN_MAINTENANCE_1_EXTENSION_NAME, m_deviceExtensionsAvailable))
    {
        pNextChainPushFront(&m_features11, &m_swapchainFeatures);
        m_deviceExtensions.push_back(VK_EXT_SWAPCHAIN_MAINTENANCE_1_EXTENSION_NAME);
    }

    // ImGui - Fix (Not using Vulkan 1.4 API)
    m_deviceExtensions.push_back(VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME);

    // Requesting all supported features, which will then be activated in the device
    // By requesting, it turns on all feature that it is supported, but the user could request specific features instead
    m_deviceFeatures.pNext = &m_features11;
    vkGetPhysicalDeviceFeatures2(m_physicalDevice, &m_deviceFeatures);

    ASSERT(m_features13.dynamicRendering, "Dynamic rendering required, update driver!");
    ASSERT(m_features13.maintenance4, "Extension VK_KHR_maintenance4 required, update driver!");  // vkGetDeviceBufferMemoryRequirementsKHR, ...
    ASSERT(m_features14.maintenance5, "Extension VK_KHR_maintenance5 required, update driver!");  // VkBufferUsageFlags2KHR, ...
    ASSERT(m_features14.maintenance6, "Extension VK_KHR_maintenance6 required, update driver!");  // vkCmdPushConstants2KHR, vkCmdBindDescriptorSets2KHR

    // Get information about what the device can do
    VkPhysicalDeviceProperties2 deviceProperties{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2 };
    deviceProperties.pNext = &m_pushDescriptorProperties;
    vkGetPhysicalDeviceProperties2(m_physicalDevice, &deviceProperties);

    // Create the logical device
    const VkDeviceCreateInfo deviceCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = &m_deviceFeatures,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &queueCreateInfo,
        .enabledExtensionCount = uint32_t(m_deviceExtensions.size()),
        .ppEnabledExtensionNames = m_deviceExtensions.data(),
    };
    VK_CHECK(vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device));
    DBG_VK_NAME(m_device);

    volkLoadDevice(m_device);  // Load all Vulkan device functions

    // Debug utility to name Vulkan objects, great in debugger like NSight
    debugUtilInitialize(m_device);

    // Get the requested queues
    vkGetDeviceQueue(m_device, m_queues[0].familyIndex, m_queues[0].queueIndex, &m_queues[0].queue);
    DBG_VK_NAME(m_queues[0].queue);

    // Log the enabled extensions
    LOGI("Enabled device extensions:");
    for (const auto& ext : m_deviceExtensions)
    {
        LOGI("  %s", ext);
    }
}

void gfx::VulkanDevice::getAvailableInstanceExtensions()
{ 
    uint32_t count{ 0 };
    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
    m_instanceExtensionsAvailable.resize(count);
    vkEnumerateInstanceExtensionProperties(nullptr, &count, m_instanceExtensionsAvailable.data());
}

void gfx::VulkanDevice::getAvailableDeviceExtensions()
{
    uint32_t count{ 0 };
    VK_CHECK(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &count, nullptr));
    m_deviceExtensionsAvailable.resize(count);
    VK_CHECK(vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &count, m_deviceExtensionsAvailable.data()));
}

bool gfx::VulkanDevice::extensionIsAvailable(const std::string& name, const std::vector<VkExtensionProperties>& extensions)
{
    for (auto& ext : extensions)
    {
        if (name == ext.extensionName)
            return true;
    }
    return false;
}

gfx::QueueInfo gfx::VulkanDevice::getQueue(VkQueueFlagBits flags) const
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties2(m_physicalDevice, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties2> queueFamilies(queueFamilyCount, { .sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
    vkGetPhysicalDeviceQueueFamilyProperties2(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

    QueueInfo queueInfo;
    for (uint32_t i = 0; i < queueFamilies.size(); i++)
    {
        if (queueFamilies[i].queueFamilyProperties.queueFlags & flags)
        {
            queueInfo.familyIndex = i;
            queueInfo.queueIndex = 0;  // A second graphic queue could be index 1 (need logic to find the right one)
            // m_queueInfo.queue = After creating the logical device
            break;
        }
    }
    return queueInfo;
}
