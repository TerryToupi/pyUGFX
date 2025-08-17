/// \cond
#ifndef __VULKAN_BIND_GROUP_LAYOUT_HPP__
#define __VULKAN_BIND_GROUP_LAYOUT_HPP__

#include <resources/bindGroupLayout.hpp>

namespace gfx
{
    class VulkanBindGroupLayout
    {
    public:
        VulkanBindGroupLayout() = default;
        VulkanBindGroupLayout(const BindGroupLayoutDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
