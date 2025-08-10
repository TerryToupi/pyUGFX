#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
    std::string messageTypeAsString;

    switch (messageType)
    {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
        messageTypeAsString = "[GENERAL]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
        messageTypeAsString = "[VALIDATION]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
        messageTypeAsString = "[PERFORMANCE]";
        break;
    case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT:
        messageTypeAsString = "[DEVICE_ADDRESS_BINDING]";
        break;
    default:
        break;
    }

    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        GFX_TRACE("{} Validation layer: {}\n", messageTypeAsString, pCallbackData->pMessage);
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        GFX_INFO("{} Validation layer: {}\n", messageTypeAsString, pCallbackData->pMessage);
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        GFX_WARN("{} Validation layer: {}\n", messageTypeAsString, pCallbackData->pMessage);
        break;
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        GFX_ERROR("{} Validation layer: {}\n", messageTypeAsString, pCallbackData->pMessage);
        break;
    default:
        break;
    }

    return VK_FALSE;
}

void gfx::VulkanDevice::Init()
{
    VK_CHECK(volkInitialize(), "Failed to initialize volk!");
    
    CreateInstance();
    SetupDebugMessenger();
    CreateSurface();
    SelectPhysicalDevice();
    CreateLogicalDevice();
}

void gfx::VulkanDevice::ShutDown()
{
    vkDeviceWaitIdle(m_Device);

    vkDestroyDevice(m_Device, nullptr);

    if (m_EnableValidationLayers)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
        {
            func(m_Instance, m_DebugMessenger, nullptr);
        }
    }

    vkDestroyInstance(m_Instance, nullptr);
}

void gfx::VulkanDevice::CreateInstance()
{
    if (m_EnableValidationLayers && !CheckValidationLayerSupport())
        GFX_ASSERT(false, "Validation layers requested, but not available!");

    // Application Info
    VkApplicationInfo appInfo =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "pyUGFX",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "pyUGFX_library",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_4,
    };

    // Instance info
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    #if defined(__APPLE__)
    {
        createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    }
    #endif

    // Get extensions.
    auto extensions = GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // Validation layers.
    if (m_EnableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
        createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = debugCallback,
        };
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    VK_CHECK(vkCreateInstance(&createInfo, nullptr, &m_Instance), "vkCreateInstance");
        
    volkLoadInstanceOnly(m_Instance);
}

void gfx::VulkanDevice::SetupDebugMessenger()
{
    if (!m_EnableValidationLayers)
    {
        return;
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = debugCallback,
    };

    VkResult result;
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        result = func(m_Instance, &createInfo, nullptr, &m_DebugMessenger);
    }
    else
    {
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    VK_CHECK(result, "vkCreateDebugUtilsMessengerEXT");
}

void gfx::VulkanDevice::CreateSurface()
{
    VulkanWindow* window = static_cast<VulkanWindow*>(gfx::Window::instance.get());
    
    window->CreateSurface(m_Instance);
}

void gfx::VulkanDevice::SelectPhysicalDevice()
{
    uint32_t deviceCount = 0;
    VK_CHECK(vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr), "vkEnumeratePhysicalDevices");

    if (deviceCount == 0)
        GFX_ASSERT(false, "Failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    VK_CHECK(vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data()), "vkEnumeratePhysicalDevices");

    m_PhysicalDevice = VK_NULL_HANDLE;

    for (const auto& device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            m_PhysicalDevice = device;
            break;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE)
        GFX_ASSERT(false, "Failed to find a suitable GPU!");

    vkGetPhysicalDeviceProperties(m_PhysicalDevice, &m_VkGPUProperties);
}

void gfx::VulkanDevice::CreateLogicalDevice()
{
    // Find queue families
    QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

    // Create queue families info
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = queueFamily,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority,
        };
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(m_DeviceExtensions.size());
    createInfo.ppEnabledExtensionNames = m_DeviceExtensions.data();

    if (m_EnableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
        createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0;
    }

    VK_CHECK(vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device), "vkCreateDevice");
    
    volkLoadDevice(m_Device);
}

// Helper

bool gfx::VulkanDevice::CheckValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : m_ValidationLayers)
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers)
        {
            if (strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
        {
            return false;
        }
    }

    return true;
}

std::vector<const char*> gfx::VulkanDevice::GetRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (m_EnableValidationLayers)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    for (const auto& instanceExtension : m_InstanceExtensions)
    {
        extensions.push_back(instanceExtension);
    }

    if (!CheckInstanceExtensionSupport(extensions))
        GFX_ASSERT(false, "Device does not support required extensions!");

    return extensions;
}

bool gfx::VulkanDevice::CheckInstanceExtensionSupport(const std::vector<const char*>& extensionNames)
{
    uint32_t extensionCount = 0;
    VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr), "vkEnumerateInstanceExtensionProperties");

    std::vector<VkExtensionProperties> extensions(extensionCount);
    VK_CHECK(vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()), "vkEnumerateInstanceExtensionProperties");

    for (const char* extensionName : extensionNames)
    {
        bool extensionFound = false;

        for (const auto& extensionProperties : extensions)
        {
            if (strcmp(extensionName, extensionProperties.extensionName) == 0)
            {
                extensionFound = true;
                break;
            }
        }

        if (!extensionFound)
        {
            return false;
        }
    }

    return true;
}

gfx::QueueFamilyIndices gfx::VulkanDevice::FindQueueFamilies(VkPhysicalDevice device)
{
    VulkanWindow* window = static_cast<VulkanWindow*>(gfx::Window::instance.get());
    
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, window->GetSurface(), &presentSupport);

        if (presentSupport)
        {
            indices.presentFamily = i;
        }

        if (indices.isComplete())
        {
            break;
        }

        i++;
    }

    return indices;
}

gfx::SwapChainSupportDetails gfx::VulkanDevice::QuerySwapChainSupport(VkPhysicalDevice device)
{
    VulkanWindow* window = static_cast<VulkanWindow*>(gfx::Window::instance.get());
    
    SwapChainSupportDetails details;

    // Formats set up.
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, window->GetSurface(), &formatCount, nullptr);

    if (formatCount != 0)
    {
        details.Formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, window->GetSurface(), &formatCount, details.Formats.data());
    }

    // Present mode set up.
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, window->GetSurface(), &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.PresentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, window->GetSurface(), &presentModeCount, details.PresentModes.data());
    }

    // Capabilities set up.
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, window->GetSurface(), &details.Capabilities);

    return details;
}

bool gfx::VulkanDevice::IsDeviceSuitable(VkPhysicalDevice device)
{
    // Find queue families
    QueueFamilyIndices indices = FindQueueFamilies(device);

    // Check device extension support
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(m_DeviceExtensions.begin(), m_DeviceExtensions.end());

    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }
    bool extensionsSupported = requiredExtensions.empty();

    bool swapChainAdequate = false;
    if (extensionsSupported)
    {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.Formats.empty() && !swapChainSupport.PresentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}
