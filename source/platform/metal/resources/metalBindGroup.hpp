/// \cond
#ifndef __METAL_BIND_GROUP_HPP__
#define __METAL_BIND_GROUP_HPP__

#include <resources/bindGroup.hpp>

namespace gfx
{
    class MetalBindGroup
    {
    public:
        MetalBindGroup(const BindGroupDescriptor&& desc);
        
    private:
        int data;
    };
}

#endif
/// \endcond
