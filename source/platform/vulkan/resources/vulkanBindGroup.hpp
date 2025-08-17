/// \cond
#ifndef __VULKAN_BIND_GROUP_HPP__
#define __VULKAN_BIND_GROUP_HPP__

#include <resources/bindGroup.hpp>

namespace gfx
{
    class VulkanBindGroup
    {
    public:
        VulkanBindGroup() = default;
        VulkanBindGroup(const BindGroupDescriptor&& desc);

        void Remove();
        
    private:
        int data = 0;
    };
}

#endif
/// \endcond
