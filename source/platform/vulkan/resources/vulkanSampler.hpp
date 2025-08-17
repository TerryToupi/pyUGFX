/// \cond
#ifndef __VULKAN_SAMPLER_HPP__
#define __VULKAN_SAMPLER_HPP__

#include <resources/sampler.hpp>

namespace gfx
{
    class VulkanSampler
    {
    public:
        VulkanSampler() = default;
        VulkanSampler(const SamplerDescriptor&& desc);

        void Remove();

    private:
        int data;
    };
}

#endif
/// \endcond
