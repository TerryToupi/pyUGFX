#include <metalWindow.hpp>

void gfx::MetalWindow::Init(const WindowDescriptor&& desc)
{
    CA::MetalLayer* layer = CA::MetalLayer::layer()->retain();
    
    layer->nextDrawable();


    
    layer->release();
}

void gfx::MetalWindow::ShutDown()
{
    
}

void gfx::MetalWindow::Run(const GameLoop& func)
{
    
}

void gfx::MetalWindow::CreateSwapChain()
{
    
}

void gfx::MetalWindow::CleanUpSwapChain()
{
    
}

void gfx::MetalWindow::ReCreateSwapChain()
{
    
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
