/**
 * @file dynamicBuffersLayout.hpp
 * @brief Defines the layout for dynamic buffers and their descriptor.
 *
 * This file declares the DynamicBuffersLayoutDescriptor structure, which specifies
 * the organization of dynamically bound buffers including slot, type, visibility,
 * offset, and range information.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __DYNAMIC_BUFFERS_LAYOUT_HPP__
#define __DYNAMIC_BUFFERS_LAYOUT_HPP__

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>

namespace gfx
{
    class DynamicBuffersLayout;

    /**
     * @brief Descriptor for creating a DynamicBuffersLayout.
     *
     * Contains information about each buffer binding, including type, shader
     * stage visibility, and memory layout (offset and range).
     */
    struct DynamicBuffersLayoutDescriptor
    {
        /**
         * @brief Represents a single buffer binding in the dynamic buffer layout.
         */
        struct BufferBinding
        {
            /// The binding slot for this buffer.
            uint32_t slot = 0;

            /// The type of buffer binding (e.g., uniform, storage).
            BufferBindingType type = BufferBindingType::UNIFORM;

            /// Shader stages that can access this buffer.
            ShaderStage visibility = ShaderStage::VERTEX | ShaderStage::FRAGMENT;

            /// Byte offset within the buffer where this binding starts.
            uint32_t byteOffset = 0;

            /// Byte size of the binding.
            uint32_t range = 0;
        };

        /// Span of all buffer bindings in this layout.
        utils::Span<BufferBinding> bufferBindings;
    };
}

#endif // !__DYNAMIC_BUFFERS_LAYOUT_HPP__
