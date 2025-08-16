/// \cond
#ifndef __VULKAN_SHADER_HPP__
#define __VULKAN_SHADER_HPP__

#include <resources/shader.hpp>

namespace gfx
{
    class VulkanShader
    {
    public:
        VulkanShader(const ShaderDescriptor&& desc);

    private:
        int data;
    };
}

#endif
/// \endcond
