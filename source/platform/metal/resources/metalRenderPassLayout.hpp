/// \cond
#ifndef __METAL_RENDER_PASS_LAYOUT_HPP__
#define __METAL_RENDER_PASS_LAYOUT_HPP__

#include <resources/renderPassLayout.hpp>

namespace gfx
{
    class MetalRenderPassLayout
    {
    public:
        MetalRenderPassLayout(const RenderPassLayoutDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
