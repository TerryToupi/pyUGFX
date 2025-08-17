/// \cond
#ifndef __METAL_SHADER_HPP__
#define __METAL_SHADER_HPP__

#include <resources/shader.hpp>

namespace gfx
{
    class MetalShader
    {
    public:
        MetalShader() = default;
        MetalShader(const ShaderDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
