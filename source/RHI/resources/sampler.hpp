/**
 * @file sampler.hpp
 * @brief Defines GPU sampler resource and its descriptor for filtering and wrapping.
 *
 * Samplers describe how textures are sampled in shaders, including filtering,
 * mipmapping, and wrapping modes.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __SAMPLER_HPP__
#define __SAMPLER_HPP__

#include <enums.hpp>

namespace gfx
{
    /**
     * @brief Represents a GPU sampler resource.
     *
     * Samplers define how textures are accessed in shaders, including filtering
     * methods, wrap modes, and comparison operations.
     */
    class Sampler;

    /**
     * @brief Descriptor for creating a GPU sampler.
     */
    struct SamplerDescriptor
    {
        /**
         * @brief Filtering options for minification, magnification, and mipmaps.
         */
        struct Filters
        {
            Filter min = Filter::NEAREST;   ///< Filter for minification.
            Filter mag = Filter::NEAREST;   ///< Filter for magnification.
            Filter mip = Filter::NEAREST;   ///< Filter for mipmapping.
        };

        Filters filters = {};                ///< Filter settings.
        Compare compareType = Compare::UNDEFINED; ///< Optional comparison mode for shadow samplers.
        Wrap wrap = Wrap::REPEAT;            ///< Texture coordinate wrap mode.
        float minMip = 0.0f;                 ///< Minimum mip level.
        float maxMip = 32.0f;                ///< Maximum mip level.
    };
}

#endif // !__SAMPLER_HPP__
