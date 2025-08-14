/// \cond
#ifndef __VULKAN_BUFFER_HPP__
#define __VULKAN_BUFFER_HPP__

#include <resources/buffer.hpp>

namespace gfx
{
    class VulkanBuffer
    {
    public:
        VulkanBuffer(const BufferDescriptor&& desc);
        
    private:
        int data;
    };
}

#endif
/// \endcond
