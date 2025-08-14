#include <iostream>
#include <window.hpp>
#include <handle.hpp>
#include <resources/buffer.hpp>
#include <context.hpp>

void run()
{
    return;
}

int main()
{
    setup::ContextInit(setup::Platforms::VULKAN);

    gfx::Window::instance->Run(run);
    
    setup::ContextShutDown();
    return 0;
}
