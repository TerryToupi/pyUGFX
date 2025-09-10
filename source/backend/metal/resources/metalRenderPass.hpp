/// \cond
#ifndef __METAL_RENDER_PASS_HPP__
#define __METAL_RENDER_PASS_HPP__

#include <resources/renderPass.hpp>

namespace gfx
{
    class MetalRenderPass
    {
    public:
        MetalRenderPass() = default;
        MetalRenderPass(const RenderPassDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
