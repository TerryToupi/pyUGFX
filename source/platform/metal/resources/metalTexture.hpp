/// \cond
#ifndef __METAL_TEXTURE_HPP__
#define __METAL_TEXTURE_HPP__

#include <resources/texture.hpp>

namespace gfx
{
    class MetalTexture
    {
    public:
        MetalTexture() = default;
        MetalTexture(const TextureDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
