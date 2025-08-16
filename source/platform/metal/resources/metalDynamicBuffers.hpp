/// \cond
#ifndef __METAL_DYNAMIC_BUFFERS_HPP__
#define __METAL_DYNAMIC_BUFFERS_HPP__

#include <resources/dynamicBuffers.hpp>

namespace gfx
{
    class MetalDynamicBuffers
    {
    public:
        MetalDynamicBuffers(const DynamicBuffersDescriptor&& desc);

    private:
        int data;
    };
}

#endif
/// \endcond
