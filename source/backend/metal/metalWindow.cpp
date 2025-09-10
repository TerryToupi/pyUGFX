/// \cond

#include <metalWindow.hpp>
#include <metalDevice.hpp>

void gfx::MetalWindow::Init(const WindowDescriptor&& desc)
{
    GFX_INFO("[Metal Window] Initiliazing Metal window!");
    if (glfwInit() != GLFW_TRUE)
        GFX_INFO("[Metal Window] Failed to initilize Metal window!");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_Window = glfwCreateWindow(desc.width, desc.height, desc.name.c_str(), nullptr, nullptr);
    
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
    {
        gfx::Window::instance->ReCreateSwapChain();
    });
}

void gfx::MetalWindow::ShutDown()
{
    CleanUpSwapChain();
    
    GFX_INFO("[Metal Window] Terminating active window!");
    glfwDestroyWindow(m_Window);
    GFX_INFO("[Metal Window] Shutting down window manager!");
    glfwTerminate();
}

void gfx::MetalWindow::Run(const GameLoop& func)
{
    while (glfwWindowShouldClose(m_Window) != GLFW_TRUE)
    {
        glfwPollEvents();
        func();
    }
}

void gfx::MetalWindow::CreateSwapChain()
{
    gfx::MetalDevice* dImpl = static_cast<gfx::MetalDevice*>(gfx::Device::instance.get());
    
    m_SwapChain = CA::MetalLayer::layer()->retain();
   
    m_SwapChain->setDevice(dImpl->GetDevice());
    m_SwapChain->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    
    m_NSwindow = get_ns_window(m_Window, m_SwapChain)->retain();
}

void gfx::MetalWindow::CleanUpSwapChain()
{
    m_SwapChain->release();
    m_NSwindow->release();
}

void gfx::MetalWindow::ReCreateSwapChain()
{
    int width = 0, height = 0;
    glfwGetFramebufferSize(m_Window, &width, &height);
    while (width == 0 || height == 0)
    {
        glfwGetFramebufferSize(m_Window, &width, &height);
        glfwWaitEvents();
    }
    
    m_SwapChain->setDrawableSize(CGSizeMake(width, height));
}

gfx::TextureFormat gfx::MetalWindow::GetSurfaceFormat()
{
    return gfx::TextureFormat::UNDEFINED;
}

void gfx::MetalWindow::GetWindowSize(int* width, int* heigh)
{
    
}

bool gfx::MetalWindow::GetKey(input::Key key)
{
    return false;
}

bool gfx::MetalWindow::GetMouseButton(input::Button button)
{
    return false;
}

void gfx::MetalWindow::GetMousePos(double* x, double* y)
{
    
}

/// \endcond
