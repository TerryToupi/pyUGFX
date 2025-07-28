#include <iostream>
#include <GLFW/glfw3.h>
#include <volk.h>
#include <assert.h>
#include <shaderc/shaderc.hpp>

int main()
{
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    glfwInit();
    assert(volkInitialize() == VK_SUCCESS);

    std::cout << "Hello World!";
    return 0;
}