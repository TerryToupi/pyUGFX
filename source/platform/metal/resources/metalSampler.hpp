/// \cond
#ifndef __METAL_SAMPLER_HPP__
#define __METAL_SAMPLER_HPP__

#include <resources/sampler.hpp>

namespace gfx
{
    class MetalSampler
    {
    public:
        MetalSampler(const SamplerDescriptor&& desc);

    private:
        int data;
    };
}

#endif
/// \endcond
