/// \cond
#ifndef __METAL_SAMPLER_HPP__
#define __METAL_SAMPLER_HPP__

#include <resources/sampler.hpp>

namespace gfx
{
    class MetalSampler
    {
    public:
        MetalSampler() = default;
        MetalSampler(const SamplerDescriptor&& desc);
    
        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
