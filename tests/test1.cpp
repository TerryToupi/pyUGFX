#include <iostream>
#include <window.hpp>
#include <handle.hpp>
#include <context.hpp>
#include <resources/resourceManger.hpp>

void run()
{
    return;
}

int main()
{
    setup::ContextInit(setup::Platforms::UNDEFINED);

    utils::Handle<gfx::Buffer> buffer = gfx::ResourceManager::instance->CreateBuffer({
            .usage = gfx::BufferUsage::VERTEX
        });

    gfx::Window::instance->Run(run);

    gfx::ResourceManager::instance->Remove(buffer);
    
    setup::ContextShutDown();
    return 0;
}
