/**
 * @file renderer.hpp
 * @brief Declares the Renderer interface for initializing, shutting down, and recording command buffers.
 *
 * This file defines the abstract Renderer class, which acts as the primary interface
 * for initializing the rendering backend, shutting it down, and beginning command
 * buffer recordings for various rendering tasks.
 *
 * @date 2025-08-13
 * author Teryy Toupi
 */

#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <common.hpp>
#include <enums.hpp>
#include <render/passRenderer.hpp>

namespace gfx
{
    /**
     * @brief Main interface for the rendering system.
     *
     * The Renderer is responsible for:
     * - Initializing the rendering backend and GPU resources.
     * - Shutting down and cleaning up resources.
     * - Creating command buffers for recording GPU work.
     *
     * This is typically implemented by a specific rendering backend
     * (e.g., Vulkan, Metal) and accessed via the static @ref instance.
     */
    class Renderer
    {
    public:
        /**
         * @brief Global static instance of the renderer.
         *
         * This should be set to a concrete backend implementation before
         * any rendering operations are performed.
         */
        static inline sPtr<Renderer> instance = nullptr;

        /**
         * @brief Initializes the rendering backend and allocates necessary resources.
         */
        virtual void Init() = 0;

        /**
         * @brief Shuts down the renderer and releases all allocated resources.
         */
        virtual void ShutDown() = 0;

        /**
         * @brief Begins recording a command buffer of the given type.
         *
         * @param type The type of command buffer to create (graphics, compute, mesh, etc.).
         * @return Pointer to the created CommandBuffer.
         */
        virtual CommandBuffer* BeginCommandRecording() = 0;
    };
}

#endif // __RENDERER_HPP__
