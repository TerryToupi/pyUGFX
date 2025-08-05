#include <iostream>
#include <window.hpp>
#include <handle.hpp>
#include <resources/buffer.hpp>
#include <context.hpp>

int main()
{
    setup::ContextInit();

    utils::Handle<gfx::Buffer> buffer;
    std::cout << "Hello World!" << std::endl;

    setup::ContextShutDown();
    return 0;
}