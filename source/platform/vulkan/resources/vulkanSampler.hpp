/// \cond
#ifndef __VULKAN_SAMPLER_HPP__
#define __VULKAN_SAMPLER_HPP__

#include <resources/sampler.hpp>

namespace gfx
{
    class VulkanSampler
    {
    public:
        VulkanSampler(const SamplerDescriptor&& desc);

    private:
        int data;
    };
}

#endif
/// \endcond
