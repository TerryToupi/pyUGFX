#include <vulkanWindow.hpp>
#include <vulkanDevice.hpp>
#include <render/VulkanRenderer.hpp>

void gfx::VulkanWindow::Init(const WindowDescriptor&& desc)
{
    m_WindowConfig = desc;
    ASSERT(glfwInit() == GLFW_TRUE, "Could not initilize GLFW!");
//    ASSERT(glfwVulkanSupported() == GLFW_TRUE, "GLFW: Vulkan not supported!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_window = glfwCreateWindow(m_WindowConfig.width, m_WindowConfig.height, m_WindowConfig.name.c_str(), nullptr, nullptr);
}

void gfx::VulkanWindow::ShutDown()
{
    swapChain.destroy();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void gfx::VulkanWindow::Run(const GameLoop& func)
{
    VulkanRenderer* renderer = static_cast<VulkanRenderer*>(gfx::Renderer::instance.get());

    while (!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) == GLFW_TRUE)
            continue;

        if (renderer->BeginFrame())
        {
            func();
            renderer->EndFrame();
        }
        else
        { /*SKIP FRAME*/ }
    }
}

gfx::TextureFormat gfx::VulkanWindow::GetSurfaceFormat()
{
	return gfx::TextureFormat();
}

bool gfx::VulkanWindow::GetWindowVSync()
{
    return m_WindowConfig.vSync;
}

void gfx::VulkanWindow::GetWindowSize(int* width, int* height)
{
    *width = (int)m_WindowConfig.width;
    *height = (int)m_WindowConfig.height;
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

void gfx::VulkanWindow::SetWindowSize(int width, int height)
{
    m_WindowConfig.width = width;
    m_WindowConfig.height = height;
}

void gfx::Swapchain::init()
{
    VkInstance instance = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getInstance();

    VK_CHECK(glfwCreateWindowSurface(instance, 
                                     static_cast<VulkanWindow*>(gfx::Window::instance.get())->m_window, 
                                     nullptr,   
                                     &m_surface));
}

void gfx::Swapchain::destroy()
{
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();
    VkInstance instance = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getInstance();

	deinitResources();

    vkDeviceWaitIdle(device);
    vkDestroySurfaceKHR(instance, m_surface, nullptr);

	*this = {};
}

VkExtent2D gfx::Swapchain::initResources(bool vSync)
{
    VkPhysicalDevice physicalDevice = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getPhysicalDevice();
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();
    
    VkExtent2D outWindowSize;

    // Query the physical device's capabilities for the given surface.
    const VkPhysicalDeviceSurfaceInfo2KHR surfaceInfo2{ .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR,
                                                       .surface = m_surface };
    VkSurfaceCapabilities2KHR             capabilities2{ .sType = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR };
    vkGetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, &surfaceInfo2, &capabilities2);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, &surfaceInfo2, &formatCount, nullptr);
    std::vector<VkSurfaceFormat2KHR> formats(formatCount, { .sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR });
    vkGetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, &surfaceInfo2, &formatCount, formats.data());

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_surface, &presentModeCount, nullptr);
    std::vector<VkPresentModeKHR> presentModes(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_surface, &presentModeCount, presentModes.data());

    // Choose the best available surface format and present mode
    const VkSurfaceFormat2KHR surfaceFormat2 = selectSwapSurfaceFormat(formats);
    const VkPresentModeKHR    presentMode = selectSwapPresentMode(presentModes, vSync);
    // Set the window size according to the surface's current extent
    outWindowSize = capabilities2.surfaceCapabilities.currentExtent;

    // Adjust the number of images in flight within GPU limitations
    uint32_t minImageCount = capabilities2.surfaceCapabilities.minImageCount;  // Vulkan-defined minimum
    uint32_t preferredImageCount = std::max(3u, minImageCount);  // Prefer 3, but respect minImageCount

    // Handle the maxImageCount case where 0 means "no upper limit"
    uint32_t maxImageCount = (capabilities2.surfaceCapabilities.maxImageCount == 0) ? preferredImageCount :  // No upper limit, use preferred
        capabilities2.surfaceCapabilities.maxImageCount;

    // Clamp preferredImageCount to valid range [minImageCount, maxImageCount]
    m_maxFramesInFlight = std::clamp(preferredImageCount, minImageCount, maxImageCount);

    // Store the chosen image format
    m_imageFormat = surfaceFormat2.surfaceFormat.format;

    // Create the swapchain itself
    const VkSwapchainCreateInfoKHR swapchainCreateInfo{
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = m_surface,
        .minImageCount = m_maxFramesInFlight,
        .imageFormat = surfaceFormat2.surfaceFormat.format,
        .imageColorSpace = surfaceFormat2.surfaceFormat.colorSpace,
        .imageExtent = capabilities2.surfaceCapabilities.currentExtent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .preTransform = capabilities2.surfaceCapabilities.currentTransform,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = presentMode,
        .clipped = VK_TRUE,
    };
    VK_CHECK(vkCreateSwapchainKHR(device, &swapchainCreateInfo, nullptr, &m_swapChain));
    DBG_VK_NAME(m_swapChain);

    // Retrieve the swapchain images
    {
        uint32_t imageCount;
        vkGetSwapchainImagesKHR(device, m_swapChain, &imageCount, nullptr);
        ASSERT(m_maxFramesInFlight <= imageCount, "Wrong swapchain setup");
        m_maxFramesInFlight = imageCount;  // Use the number of images in the swapchain
    }
    std::vector<VkImage> swapImages(m_maxFramesInFlight);
    vkGetSwapchainImagesKHR(device, m_swapChain, &m_maxFramesInFlight, swapImages.data());

    // Store the swapchain images and create views for them
    m_nextImages.resize(m_maxFramesInFlight);
    VkImageViewCreateInfo imageViewCreateInfo{
        .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
        .viewType = VK_IMAGE_VIEW_TYPE_2D,
        .format = m_imageFormat,
        .components = {.r = VK_COMPONENT_SWIZZLE_IDENTITY, .g = VK_COMPONENT_SWIZZLE_IDENTITY, .b = VK_COMPONENT_SWIZZLE_IDENTITY, .a = VK_COMPONENT_SWIZZLE_IDENTITY},
        .subresourceRange = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .baseMipLevel = 0, .levelCount = 1, .baseArrayLayer = 0, .layerCount = 1},
    };
    for (uint32_t i = 0; i < m_maxFramesInFlight; i++)
    {
        m_nextImages[i].image = swapImages[i];
        DBG_VK_NAME(m_nextImages[i].image);
        imageViewCreateInfo.image = m_nextImages[i].image;
        VK_CHECK(vkCreateImageView(device, &imageViewCreateInfo, nullptr, &m_nextImages[i].imageView));
        DBG_VK_NAME(m_nextImages[i].imageView);
    }

    // Initialize frame resources for each frame
    m_frameResources.resize(m_maxFramesInFlight);
    for (size_t i = 0; i < m_maxFramesInFlight; ++i)
    {
        /*--
         * The sync objects are used to synchronize the rendering with the presentation.
         * The image available semaphore is signaled when the image is available to render.
         * The render finished semaphore is signaled when the rendering is finished.
         * The in flight fence is signaled when the frame is in flight.
        -*/
        const VkSemaphoreCreateInfo semaphoreCreateInfo{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
        VK_CHECK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_frameResources[i].imageAvailableSemaphore));
        DBG_VK_NAME(m_frameResources[i].imageAvailableSemaphore);
        VK_CHECK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_frameResources[i].renderFinishedSemaphore));
        DBG_VK_NAME(m_frameResources[i].renderFinishedSemaphore);
    }

    // Transition images to present layout
    {
        VkCommandBuffer cmd = static_cast<VulkanRenderer*>(gfx::Renderer::instance.get())->
            BeginSingleTimeCommandRecording();

        for (uint32_t i = 0; i < m_maxFramesInFlight; i++)
        {
            static_cast<VulkanRenderer*>(gfx::Renderer::instance.get())->
                cmdTransitionImageLayout(cmd, m_nextImages[i].image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
        }
        static_cast<VulkanRenderer*>(gfx::Renderer::instance.get())->
            EndSingleTimeCommandRecording(cmd);
    }

    return outWindowSize;
}

VkExtent2D gfx::Swapchain::reinitResources(bool vSync)
{
    gfx::QueueInfo queue = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getGraphicsQueue();

    // Wait for all frames to finish rendering before recreating the swapchain
    vkQueueWaitIdle(queue.queue);

    m_frameResourceIndex = 0;
    m_needRebuild = false;
    deinitResources();
    return initResources(vSync);
}

void gfx::Swapchain::deinitResources()
{
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();

    vkDestroySwapchainKHR(device, m_swapChain, nullptr);
    for (auto& frameRes : m_frameResources)
    {
        vkDestroySemaphore(device, frameRes.imageAvailableSemaphore, nullptr);
        vkDestroySemaphore(device, frameRes.renderFinishedSemaphore, nullptr);
    }
    for (auto& image : m_nextImages)
    {
        vkDestroyImageView(device, image.imageView, nullptr);
    }
}

VkResult gfx::Swapchain::acquireNextImage()
{
    ASSERT(m_needRebuild == false, "Swapbuffer need to call reinitResources()");

    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();

    auto& frame = m_frameResources[m_frameResourceIndex];

    // Acquire the next image from the swapchain
    const VkResult result = vkAcquireNextImageKHR(device, m_swapChain, std::numeric_limits<uint64_t>::max(),
        frame.imageAvailableSemaphore, VK_NULL_HANDLE, &m_frameImageIndex);
    // Handle special case if the swapchain is out of date (e.g., window resize)
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        m_needRebuild = true;  // Swapchain must be rebuilt on the next frame
    }
    else
    {
        ASSERT(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR, "Couldn't aquire swapchain image");
    }
    return result;
}

void gfx::Swapchain::presentFrame(VkQueue queue)
{
    auto& frame = m_frameResources[m_frameImageIndex];

    // Setup the presentation info, linking the swapchain and the image index
    const VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,                               // Wait for rendering to finish
        .pWaitSemaphores = &frame.renderFinishedSemaphore,  // Synchronize presentation
        .swapchainCount = 1,                               // Swapchain to present the image
        .pSwapchains = &m_swapChain,                    // Pointer to the swapchain
        .pImageIndices = &m_frameImageIndex,              // Index of the image to present
    };

    // Present the image and handle potential resizing issues
    const VkResult result = vkQueuePresentKHR(queue, &presentInfo);
    // If the swapchain is out of date (e.g., window resized), it needs to be rebuilt
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        m_needRebuild = true;
    }
    else
    {
        ASSERT(result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR, "Couldn't present swapchain image");
    }

    // Advance to the next frame in the swapchain
    m_frameResourceIndex = (m_frameResourceIndex + 1) % m_maxFramesInFlight;
}

VkSurfaceFormat2KHR gfx::Swapchain::selectSwapSurfaceFormat(const std::vector<VkSurfaceFormat2KHR>& availableFormats) const
{
    // If there's only one available format and it's undefined, return a default format.
    if (availableFormats.size() == 1 && availableFormats[0].surfaceFormat.format == VK_FORMAT_UNDEFINED)
    {
        VkSurfaceFormat2KHR result{ .sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR,
                                   .surfaceFormat = {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR} };
        return result;
    }

    const auto preferredFormats = std::to_array<VkSurfaceFormat2KHR>({
        {.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR, .surfaceFormat = {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR}},
        {.sType = VK_STRUCTURE_TYPE_SURFACE_FORMAT_2_KHR, .surfaceFormat = {VK_FORMAT_R8G8B8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR}},
        });

    // Check available formats against the preferred formats.
    for (const auto& preferredFormat : preferredFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.surfaceFormat.format == preferredFormat.surfaceFormat.format
                && availableFormat.surfaceFormat.colorSpace == preferredFormat.surfaceFormat.colorSpace)
            {
                return availableFormat;  // Return the first matching preferred format.
            }
        }
    }

    // If none of the preferred formats are available, return the first available format.
    return availableFormats[0];
}

VkPresentModeKHR gfx::Swapchain::selectSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes, bool vSync)
{
    if (vSync)
    {
        return VK_PRESENT_MODE_FIFO_KHR;
    }

    bool mailboxSupported = false, immediateSupported = false;

    for (VkPresentModeKHR mode : availablePresentModes)
    {
        if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
            mailboxSupported = true;
        if (mode == VK_PRESENT_MODE_IMMEDIATE_KHR)
            immediateSupported = true;
    }

    if (mailboxSupported)
    {
        return VK_PRESENT_MODE_MAILBOX_KHR;
    }

    if (immediateSupported)
    {
        return VK_PRESENT_MODE_IMMEDIATE_KHR;  // Best mode for low latency
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}
