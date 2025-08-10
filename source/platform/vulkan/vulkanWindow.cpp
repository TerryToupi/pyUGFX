#include <vulkanWindow.hpp>

void gfx::VulkanWindow::Init(const WindowDescriptor&& desc)
{
    GFX_INFO("[Vulkan Window] Initiliazing Vulkan window!");
    if (glfwInit() != GLFW_TRUE)
        GFX_INFO("[Vulkan Window] Failed to initilize Vulkan window!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(desc.width, desc.height, desc.name.c_str(), nullptr, nullptr);
}

void gfx::VulkanWindow::ShutDown()
{
    GFX_INFO("[Vulkan Window] Terminating active window!");
    glfwDestroyWindow(m_Window);
    GFX_INFO("[Vulkan Window] Shutting down window manager!");
    glfwTerminate();
}

void gfx::VulkanWindow::Run(const GameLoop& func)
{
    while (glfwWindowShouldClose(m_Window) != GLFW_TRUE)
    {
        glfwPollEvents();
        func();
    }
}

gfx::TextureFormat gfx::VulkanWindow::GetSurfaceFormat()
{
    
}

void gfx::VulkanWindow::GetWindowSize(int* width, int* heigh)
{
    
}

bool gfx::VulkanWindow::GetKey(input::Key key)
{
    
}

bool gfx::VulkanWindow::GetMouseButton(input::Button button)
{
    
}

void gfx::VulkanWindow::GetMousePos(double* x, double* y)
{
    
}

void gfx::VulkanWindow::CreateSurface(VkInstance instance)
{
    VK_CHECK(glfwCreateWindowSurface(instance, m_Window, nullptr, &m_Surface), "Failed To create Vulkan Surface!");
}

void gfx::VulkanWindow::CreateSwapchain()
{
    
}

void gfx::VulkanWindow::CleanupSwapchain()
{
    
}

void gfx::VulkanWindow::ReCreateSwapChain()
{
    int width = 0, height = 0;
    glfwGetFramebufferSize(m_Window, &width, &height);
    while (width == 0 || height == 0) {
        glfwGetFramebufferSize(m_Window, &width, &height);
        glfwWaitEvents();
    }
//    vkDeviceWaitIdle(ctx.device);
    CleanupSwapchain();
    CreateSwapchain();
}

GLFWwindow* gfx::VulkanWindow::GetWindow()
{
    return m_Window;
}

VkSurfaceKHR gfx::VulkanWindow::GetSurface()
{
    return m_Surface;
}
