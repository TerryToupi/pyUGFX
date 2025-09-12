#include <iostream>
#include <window.hpp>
#include <handle.hpp>
#include <context.hpp>
#include <resources/resourceManger.hpp>
#include <render/renderer.hpp>

void run()
{
    // requestign command buffer once per frame
    gfx::CommandBuffer* buffer = gfx::Renderer::instance->BeginCommandRecording();

    uint32_t buf[1024];
    buffer->BeginRenderPass({
        .swapTarget = {
            .enabled = true,
            .clearColor = {1.0, 1.0, 1.0, 1.0}
        }
    }, utils::Span<uint32_t>(buf));
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
