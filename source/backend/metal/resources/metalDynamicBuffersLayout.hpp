/// \cond
#ifndef __METAL_DYNAMIC_BUFFERS_LAYOUT_HPP__
#define __METAL_DYNAMIC_BUFFERS_LAYOUT_HPP__

#include <resources/dynamicBuffers.hpp>

namespace gfx
{
    class MetalDynamicBuffersLayout
    {
    public:
        MetalDynamicBuffersLayout() = default;
        MetalDynamicBuffersLayout(const DynamicBuffersLayoutDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
