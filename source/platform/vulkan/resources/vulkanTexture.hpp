/// \cond
#ifndef __VULKAN_TEXTURE_HPP__
#define __VULKAN_TEXTURE_HPP__

#include <resources/texture.hpp>

namespace gfx
{
    class VulkanTexture
    {
    public:
        VulkanTexture() = default;
        VulkanTexture(const TextureDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
