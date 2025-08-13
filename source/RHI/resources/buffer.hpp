/**
 * @file buffer.hpp
 * @brief Defines the Buffer resource and its descriptor for GPU memory allocation.
 *
 * This file declares the BufferDescriptor structure, which specifies
 * the type, usage, and initial data for a GPU buffer.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <enums.hpp>
#include <span.hpp>

namespace gfx
{
    class Buffer;

    /**
     * @brief Describes a GPU buffer and its properties.
     *
     * A BufferDescriptor specifies the intended usage of the buffer,
     * allocation size, and optional initial data to upload.
     */
    struct BufferDescriptor
    {
        /// The usage flags of the buffer (e.g., uniform, storage, index, vertex).
        gfx::BufferUsage usage = gfx::BufferUsage::UNIFORM;

        /// Performance or update hint (static, dynamic, etc.).
        gfx::BufferUsageHint hint = gfx::BufferUsageHint::STATIC;

        /// Size of the buffer in bytes.
        uint64_t byteSize = 0;

        /// Optional initial data to populate the buffer.
        utils::Span<uint8_t> initialData;
    };
}

#endif // !__BUFFER_HPP__
