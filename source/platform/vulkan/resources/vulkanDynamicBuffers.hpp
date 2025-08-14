/// \cond
#ifndef __VULKAN_DYNAMIC_BUFFERS_HPP__
#define __VULKAN_DYNAMIC_BUFFERS_HPP__

#include <resources/dynamicBuffers.hpp>

namespace gfx
{
    class VulkanDynamicBuffers
    {
    public:
        VulkanDynamicBuffers(const DynamicBuffersDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
