/// \cond
#ifndef __METAL_TEXTURE_HPP__
#define __METAL_TEXTURE_HPP__

#include <resources/texture.hpp>

namespace gfx
{
    class MetalTexture
    {
    public:
        MetalTexture(const TextureDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
