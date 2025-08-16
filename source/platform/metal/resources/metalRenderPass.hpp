/// \cond
#ifndef __METAL_RENDER_PASS_HPP__
#define __MTEAL_RENDER_PASS_HPP__

#include <resources/renderPass.hpp>

namespace gfx
{
    class MetalRenderPass
    {
    public:
        MetalRenderPass(const RenderPassDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
