/// \cond
#ifndef __VULKAN_BIND_GROUP_HPP__
#define __VULKAN_BIND_GROUP_HPP__

#include <resources/bindGroup.hpp>

namespace gfx
{
    class VulkanBindGroup
    {
    public:
        VulkanBindGroup(const BindGroupDescriptor&& desc);
        
    private:
        int data;
    };
}

#endif
/// \endcond
