#include <metalDevice.hpp>
#include <Metal.hpp>

#include <GLFW/glfw3.h>

void gfx::MetalDevice::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Heavy", NULL, NULL);
    
    MTL::Device* device = MTL::CreateSystemDefaultDevice();
    CA::MetalLayer* layer = CA::MetalLayer::layer()->retain();
    
    layer->setDevice(device);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    
    layer->release();
}

void gfx::MetalDevice::ShutDown()
{
}
