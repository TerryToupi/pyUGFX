#include <iostream>
#include <window.hpp>
#include <handle.hpp>
#include <context.hpp>
#include <resources/resourceManger.hpp>
#include <render/renderer.hpp>

void run()
{
    gfx::CommandBuffer* buffer = gfx::Renderer::instance->BeginCommandRecording(gfx::CommandBufferType::MAIN);
    buffer->Submit();
    return;
}

int main()
{
    setup::ContextInit(setup::Platforms::VULKAN);

    utils::Handle<gfx::Buffer> buffer = gfx::ResourceManager::instance->CreateBuffer({
            .usage = gfx::BufferUsage::VERTEX
        });

    gfx::Window::instance->Run(run);

    gfx::ResourceManager::instance->Remove(buffer);
    
    setup::ContextShutDown();
    return 0;
}
