#include <metalDevice.hpp>
#include <metalWindow.hpp>

void gfx::MetalDevice::Init()
{
    m_Device = MTL::CreateSystemDefaultDevice()->retain();
    GFX_ASSERT(m_Device != nullptr, "Failed to create Metal Device!");
    
    MetalWindow* window = static_cast<MetalWindow*>(gfx::Window::instance.get());
    window->CreateSwapChain();
}

void gfx::MetalDevice::ShutDown()
{
    m_Device->release();
}

MTL::Device* gfx::MetalDevice::GetDevice()
{
    return m_Device;
}
