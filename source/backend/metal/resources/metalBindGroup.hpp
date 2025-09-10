/// \cond
#ifndef __METAL_BIND_GROUP_HPP__
#define __METAL_BIND_GROUP_HPP__

#include <resources/bindGroup.hpp>

namespace gfx
{
    class MetalBindGroup
    {
    public:
        MetalBindGroup() = default;
        MetalBindGroup(const BindGroupDescriptor&& desc);

        void Remove();
        
    private:
        int data;
    };
}

#endif
/// \endcond
