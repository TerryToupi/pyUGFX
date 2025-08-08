#include <metalDevice.hpp>
#include <Metal.hpp>

void gfx::MetalDevice::Init()
{
    MTL::Device* device = MTL::CreateSystemDefaultDevice();
    CA::MetalLayer* layer = CA::MetalLayer::layer()->retain();
    
    layer->setDevice(device);
    
    layer->release();
}

void gfx::MetalDevice::ShutDown()
{
}
