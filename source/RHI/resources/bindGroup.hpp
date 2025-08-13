/**
 * @file bind_group.hpp
 * @brief Defines the BindGroup and its descriptor structure for binding resources to shaders.
 *
 * This file declares the BindGroupDescriptor structure, which describes
 * the layout and resources (buffers, textures, samplers) bound to a pipeline.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __BIND_GROUP_HPP__
#define __BIND_GROUP_HPP__

#include <span.hpp>
#include <handle.hpp>

#include <enums.hpp>
#include <resources/bindGroupLayout.hpp>
#include <resources/texture.hpp>
#include <resources/sampler.hpp>
#include <resources/buffer.hpp>

namespace gfx
{
    class BindGroup;

    /**
     * @brief Describes the resources bound to a shader pipeline.
     *
     * A BindGroupDescriptor contains:
     * - The layout describing the types and slots of resources.
     * - Buffers, textures, and samplers to bind to the GPU.
     */
    struct BindGroupDescriptor
    {
        /// Handle to the layout describing the binding slots and types.
        utils::Handle<BindGroupLayout> layout;

        /**
         * @brief Represents a buffer bound to a specific slot.
         */
        struct BufferEntry
        {
            /// The binding slot index for this buffer.
            uint32_t slot = 0;
            
            /// Handle to the buffer resource.
            utils::Handle<Buffer> buffer;
        };
        /// Span of buffers to bind.
        utils::Span<BufferEntry> buffers;
        
        /**
         * @brief Represents a texture bound to a specific slot.
         */
        struct TextureEntry
        {
            /// The binding slot index for this texture.
            uint32_t slot = 0;
            
            /// Handle to the texture resource.
            utils::Handle<Texture> texture;
        };
        /// Span of textures to bind.
        utils::Span<TextureEntry> textures;
        
        /**
         * @brief Represents a sampler bound to a specific slot.
         */
        struct SamplerEntry
        {
            /// The binding slot index for this sampler.
            uint32_t slot = 0;
            
            /// Handle to the sampler resource.
            utils::Handle<Sampler> sampler;
        };
        /// Span of samplers to bind.
        utils::Span<SamplerEntry> samplers;
    };
}

#endif // !__BIND_GROUP_HPP__
