/// \cond
#ifndef __METAL_RENDER_PASS_LAYOUT_HPP__
#define __METAL_RENDER_PASS_LAYOUT_HPP__

#include <resources/renderPassLayout.hpp>

namespace gfx
{
    class MetalRenderPassLayout
    {
    public:
        MetalRenderPassLayout() = default;
        MetalRenderPassLayout(const RenderPassLayoutDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
