/// \cond
#ifndef __VULKAN_TEXTURE_HPP__
#define __VULKAN_TEXTURE_HPP__

#include <resources/texture.hpp>

namespace gfx
{
    class VulkanTexture
    {
    public:
        VulkanTexture(const TextureDescriptor&& desc);

    private:
        int data;
    };
}

#endif
/// \endcond
