/// \cond
#ifndef __VULKAN_BIND_GROUP_LAYOUT_HPP__
#define __VULKAN_BIND_GROUP_LAYOUT_HPP__

#include <resources/bindGroupLayout.hpp>

namespace gfx
{
    class VulkanBindGroupLayout
    {
    public:
        VulkanBindGroupLayout(const BindGroupLayoutDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
