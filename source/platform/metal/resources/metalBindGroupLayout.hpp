/// \cond
#ifndef __METAL_BIND_GROUP_LAYOUT_HPP__
#define __METAL_BIND_GROUP_LAYOUT_HPP__

#include <resources/bindGroupLayout.hpp>

namespace gfx
{
    class MetalBindGroupLayout
    {
    public:
        MetalBindGroupLayout(const BindGroupLayoutDescriptor&& desc);
        
    private:
        int data;
    }
}

#endif
/// \endcond
