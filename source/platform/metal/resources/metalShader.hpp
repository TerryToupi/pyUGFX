/// \cond
#ifndef __METAL_SHADER_HPP__
#define __METAL_SHADER_HPP__

#include <resources/shader.hpp>

namespace gfx
{
    class MetalShader
    {
    public:
        MetalShader(const ShaderDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
