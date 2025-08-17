/// \cond
#ifndef __VULKAN_DYNAMIC_BUFFERS_LAYOUT_HPP__
#define __VULKAN_DYNAMIC_BUFFERS_LAYOUT_HPP__

#include <resources/dynamicBuffers.hpp>

namespace gfx
{
    class VulkanDynamicBuffersLayout
    {
    public:
        VulkanDynamicBuffersLayout() = default;
        VulkanDynamicBuffersLayout(const DynamicBuffersLayoutDescriptor&& desc);
        
        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
