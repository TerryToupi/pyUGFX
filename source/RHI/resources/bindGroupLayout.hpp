/**
 * @file bind_group_layout.hpp
 * @brief Defines the BindGroupLayout and its descriptor for shader resource bindings.
 *
 * This file declares the BindGroupLayoutDescriptor structure, which describes
 * how buffers, textures, and samplers are bound to shader stages.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __BIND_GROUP_LAYOUT_HPP__
#define __BIND_GROUP_LAYOUT_HPP__

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>

namespace gfx
{
    class BindGroupLayout;

    /**
     * @brief Describes the layout of resources bound to a shader pipeline.
     *
     * This structure specifies which buffers, textures, and samplers are
     * available in the bind group and their visibility across shader stages.
     */
    struct BindGroupLayoutDescriptor
    {
        /**
         * @brief Represents a buffer binding within the layout.
         */
        struct BufferBinding
        {
            /// The binding slot index for this buffer.
            uint32_t slot = 0;

            /// Type of buffer binding (uniform, storage, etc.).
            BufferBindingType type = BufferBindingType::UNIFORM;

            /// Shader stages that can access this buffer.
            ShaderStage visibility = ShaderStage::VERTEX | ShaderStage::FRAGMENT;
        };
        /// Span of buffer bindings in the layout.
        utils::Span<BufferBinding> bufferBindings;

        /**
         * @brief Represents a texture binding within the layout.
         */
        struct TextureBinding
        {
            /// The binding slot index for this texture.
            uint32_t slot = 0;

            /// Type of texture sampling (float, int, etc.).
            TextureSampleType sampleType = TextureSampleType::FLOAT;

            /// Dimension of the texture view (1D, 2D, 3D, Cube, etc.).
            TextureDimention viewDimention = TextureDimention::D2;

            /// Shader stages that can access this texture.
            ShaderStage visibility = ShaderStage::VERTEX | ShaderStage::FRAGMENT;
        };
        /// Span of texture bindings in the layout.
        utils::Span<TextureBinding> textureBindings;

        /**
         * @brief Represents a sampler binding within the layout.
         */
        struct SamplerBinding
        {
            /// The binding slot index for this sampler.
            uint32_t slot = 0;

            /// Whether this sampler is a comparison sampler.
            bool comparison = false;

            /// Shader stages that can access this sampler.
            ShaderStage visibility = ShaderStage::VERTEX | ShaderStage::FRAGMENT;
        };
        /// Span of sampler bindings in the layout.
        utils::Span<SamplerBinding> samplerBindings;
    };
}

#endif // !__BIND_GROUP_LAYOUT_HPP__
