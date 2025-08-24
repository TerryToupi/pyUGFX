#include <iostream>
#include <window.hpp>
#include <handle.hpp>
#include <context.hpp>
#include <resources/resourceManger.hpp>
#include <render/renderer.hpp>

void run()
{
    uint32_t buf[1024];
    gfx::CommandBuffer* buffer = gfx::Renderer::instance->BeginCommandRecording(gfx::CommandBufferType::MAIN);
    buffer->BeginRenderPass({
        .depthTarget = {
            .enabled = false
        },
        .colorTargets = {
            {.isSwapChain = true}
        },
    }, utils::Span<uint32_t>(buf));
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
