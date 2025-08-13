/**
 * @file texture.hpp
 * @brief Defines GPU texture resource and its creation descriptor.
 *
 * Textures store image data for sampling in shaders. They can be 1D, 2D, 3D, or array types,
 * and may include multiple mipmap levels. Textures are associated with GPU usage flags
 * and may contain initial data for upload.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <climits>

#include <span.hpp>
#include <enums.hpp>

namespace gfx
{
    /**
     * @brief Represents a GPU texture resource.
     */
    class Texture;

    /**
     * @brief Descriptor used to create a texture resource.
     */
    struct TextureDescriptor
    {
        gfx::TextureFormat format = gfx::TextureFormat::RGBA8_UNORM;  ///< Texture pixel format.
        gfx::TextureUsage usage = gfx::TextureUsage::TEXTURE_BINDING | gfx::TextureUsage::COPY_DST; ///< Usage flags.
        gfx::TextureType type = gfx::TextureType::D2;                 ///< Type of texture (1D, 2D, 3D, cube, etc.).
        uint32_t width = 0;                                           ///< Width in pixels.
        uint32_t height = 0;                                          ///< Height in pixels.
        uint32_t depth = 1;                                           ///< Depth or array layers.
        uint32_t mipLevelCount = 1;                                   ///< Number of mipmap levels.
        uint32_t samplerCount = 1;                                    ///< Number of samplers that can bind this texture.

        utils::Span<uint8_t> initialData;                             ///< Optional initial pixel data to upload.
    };
}

#endif // !__TEXTURE_HPP__
