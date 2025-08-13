/**
 * @file dynamicBuffers.hpp
 * @brief Defines the DynamicBuffers resource and its descriptor.
 *
 * This file declares the DynamicBuffersDescriptor structure, which specifies
 * a set of dynamically bound buffers with offsets and ranges for GPU use.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __DYNAMIC_BUFFER_HPP__
#define __DYNAMIC_BUFFER_HPP__

#include <enums.hpp>
#include <handle.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffersLayout.hpp>

namespace gfx
{
    class DynamicBuffers;

    /**
     * @brief Descriptor for creating a DynamicBuffers object.
     *
     * Contains references to the layout and the individual buffers,
     * along with offsets and ranges for each buffer.
     */
    struct DynamicBuffersDescriptor
    {
        /// Handle to the dynamic buffer layout describing structure of all buffers.
        utils::Handle<DynamicBuffersLayout> dynamicBuffersLayout;

        /**
         * @brief Represents a single buffer entry in a dynamic buffer set.
         */
        struct BufferEntry
        {
            /// The binding slot for this buffer.
            uint32_t slot = 0;

            /// Handle to the actual GPU buffer.
            utils::Handle<Buffer> buffer;

            /// Byte offset within the buffer where the data starts.
            uint32_t byteOffset = 0;

            /// Range (size in bytes) of this buffer binding.
            uint32_t range = 0;
        };
        /// Span of all buffer entries in this dynamic buffer.
        utils::Span<BufferEntry> buffers;
    };
}

#endif // !__DYNAMIC_BUFFER_HPP__
