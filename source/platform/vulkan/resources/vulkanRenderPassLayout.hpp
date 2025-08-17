/// \cond
#ifndef __VULKAN_RENDER_PASS_LAYOUT_HPP__
#define __VULKAN_RENDER_PASS_LAYOUT_HPP__

#include <resources/renderPassLayout.hpp>

namespace gfx
{
    class VulkanRenderPassLayout
    {
    public:
        VulkanRenderPassLayout() = default;
        VulkanRenderPassLayout(const RenderPassLayoutDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
