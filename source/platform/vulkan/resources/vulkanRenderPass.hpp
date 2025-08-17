/// \cond
#ifndef __VULKAN_RENDER_PASS_HPP__
#define __VULKAN_RENDER_PASS_HPP__

#include <resources/renderPass.hpp>

namespace gfx
{
    class VulkanRenderPass
    {
    public:
        VulkanRenderPass() = default;
        VulkanRenderPass(const RenderPassDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
