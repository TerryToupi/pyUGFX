/// \cond

#include <vulkanWindow.hpp>
#include <vulkanDevice.hpp>
#include <render/vulkanRenderer.hpp>

void gfx::VulkanWindow::Init(const WindowDescriptor&& desc)
{
    GFX_INFO("[Vulkan Window] Initiliazing Vulkan window!");
    if (glfwInit() != GLFW_TRUE)
        GFX_INFO("[Vulkan Window] Failed to initilize Vulkan window!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(desc.width, desc.height, desc.name.c_str(), nullptr, nullptr);
    
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
    {
        gfx::Window::instance->ReCreateSwapChain();
    });
}

void gfx::VulkanWindow::ShutDown()
{
    VulkanDevice* dImpl = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    
    vkDeviceWaitIdle(dImpl->GetDevice());
    CleanUpSwapChain();
    vkDestroySurfaceKHR(dImpl->GetInstance(), m_Surface, nullptr);
    
    GFX_INFO("[Vulkan Window] Terminating active window!");
    glfwDestroyWindow(m_Window);
    GFX_INFO("[Vulkan Window] Shutting down window manager!");
    glfwTerminate();
}

void gfx::VulkanWindow::Run(const GameLoop& func)
{
    gfx::VulkanRenderer* renderer = static_cast<gfx::VulkanRenderer*>(gfx::Renderer::instance.get());

    while (glfwWindowShouldClose(m_Window) != GLFW_TRUE)
    {
        glfwPollEvents();

        renderer->BeginFrame();
        {
			GetNextSwapChainImage();
			func();
        }
        renderer->EndFrame();

        Present();
    }
}

gfx::TextureFormat gfx::VulkanWindow::GetSurfaceFormat()
{
    return gfx::TextureFormat::UNDEFINED;
}

void gfx::VulkanWindow::GetWindowSize(int* width, int* heigh)
{
    
}

bool gfx::VulkanWindow::GetKey(input::Key key)
{
    return false;
}

bool gfx::VulkanWindow::GetMouseButton(input::Button button)
{
    return false;
}

void gfx::VulkanWindow::GetMousePos(double* x, double* y)
{
    
}

void gfx::VulkanWindow::CreateSurface(VkInstance instance)
{
    VK_CHECK(glfwCreateWindowSurface(instance, m_Window, nullptr, &m_Surface), "Failed To create Vulkan Surface!");
}

void gfx::VulkanWindow::GetNextSwapChainImage()
{
    gfx::VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    gfx::VulkanRenderer* renderer = static_cast<VulkanRenderer*>(gfx::Renderer::instance.get());

    VK_CHECK(vkAcquireNextImageKHR(device->GetDevice(), m_Swapchain, 1000000000, renderer->GetImageAvailableSemaphore(), nullptr, &m_SwapchainIndex), "vkAcquireNextImageKHR");
}

void gfx::VulkanWindow::Present()
{
    gfx::VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    gfx::VulkanRenderer* renderer = static_cast<VulkanRenderer*>(gfx::Renderer::instance.get());

    VkSemaphore imageAvailable = renderer->GetImageAvailableSemaphore();
    VkPresentInfoKHR presentInfo =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = nullptr,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &imageAvailable,
        .swapchainCount = 1,
        .pSwapchains = &m_Swapchain,
        .pImageIndices = &m_SwapchainIndex,
    };
    VK_CHECK(vkQueuePresentKHR(renderer->GetPresentQueue(), &presentInfo));
}

void gfx::VulkanWindow::CreateSwapChain()
{
    VulkanDevice* dImpl = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    
    // Query surface capabilities
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dImpl->GetAdapter(), m_Surface, &capabilities);

    // Choose surface format
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(dImpl->GetAdapter(), m_Surface, &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(dImpl->GetAdapter(), m_Surface, &formatCount, formats.data());
    auto surfaceFormat = ChooseSurfaceFormat(formats);

    // Choose present mode
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(dImpl->GetAdapter(), m_Surface, &presentModeCount, nullptr);
    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(dImpl->GetAdapter(), m_Surface, &presentModeCount, presentModes.data());
    auto presentMode = ChoosePresentMode(presentModes);

    // Choose extent
    VkExtent2D extent = ChooseExtent(capabilities);

    uint32_t imageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
    {
        imageCount = capabilities.maxImageCount;
    }

    // Create swapchain
    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = m_Surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t queueFamilyIndices[] = { dImpl->GetQueueIndicies().graphicsFamily.value() };
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 1;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;

    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    
    VK_CHECK(vkCreateSwapchainKHR(dImpl->GetDevice(), &createInfo, nullptr, &m_Swapchain), "vkCreateSwapchainKHR");

    // Get swapchain images
    vkGetSwapchainImagesKHR(dImpl->GetDevice(), m_Swapchain, &imageCount, nullptr);
    m_SwapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(dImpl->GetDevice(), m_Swapchain, &imageCount, m_SwapchainImages.data());

    m_SwapchainImageFormat = surfaceFormat.format;
    m_SwapchainExtent = extent;

    // Create image views
    m_SwapchainImageViews.resize(m_SwapchainImages.size());
    for (size_t i = 0; i < m_SwapchainImages.size(); i++)
    {
        m_SwapchainImageViews[i] = CreateImageView(m_SwapchainImages[i], m_SwapchainImageFormat);
    }
}

void gfx::VulkanWindow::CleanUpSwapChain()
{
    VulkanDevice* dImpl = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    
    for (auto view : m_SwapchainImageViews)
    {
        vkDestroyImageView(dImpl->GetDevice(), view, nullptr);
    }
    
    vkDestroySwapchainKHR(dImpl->GetDevice(), m_Swapchain, nullptr);
    
    m_SwapchainImages.clear();
    m_SwapchainImageViews.clear();
}

void gfx::VulkanWindow::ReCreateSwapChain()
{
    VulkanDevice* dImpl = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    
    int width = 0, height = 0;
    glfwGetFramebufferSize(m_Window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(m_Window, &width, &height);
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(dImpl->GetDevice());
    CleanUpSwapChain();
    CreateSwapChain();
}

VkSurfaceFormatKHR gfx::VulkanWindow::ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats)
{
    for (const auto& availableFormat : formats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }
    return formats[0];
}

VkPresentModeKHR gfx::VulkanWindow::ChoosePresentMode(const std::vector<VkPresentModeKHR>& modes)
{
    for (const auto& availablePresentMode : modes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR; // guaranteed to be supported
}

VkExtent2D gfx::VulkanWindow::ChooseExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {
        int width, height;
        glfwGetFramebufferSize(m_Window, &width, &height);
        VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
        return actualExtent;
    }
}

VkImageView gfx::VulkanWindow::CreateImageView(VkImage image, VkFormat format)
{
    VulkanDevice* dImpl = static_cast<VulkanDevice*>(gfx::Device::instance.get());
    
    VkImageViewCreateInfo viewInfo{};
    viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewInfo.image = image;
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    VkImageView imageView;
    VK_CHECK(vkCreateImageView(dImpl->GetDevice(), &viewInfo, nullptr, &imageView), "vkCreateImageView");
    return imageView;
}

GLFWwindow* gfx::VulkanWindow::GetWindow()
{
    return m_Window;
}

VkSurfaceKHR gfx::VulkanWindow::GetSurface()
{
    return m_Surface;
}

/// \endcond
