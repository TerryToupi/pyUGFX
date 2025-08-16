/// \cond
#ifndef __METAL_BUFFER_HPP__
#define __METAL_BUFFER_HPP__

#include <resources/buffer.hpp>

namespace gfx
{
    class MetalBuffer
    {
    public:
        MetalBuffer(const BufferDescriptor&& desc);
        
    private:
        int data;
    };
}

#endif
/// \endcond
