/**
 * @file pass_renderer.hpp
 * @brief Defines the CommandBuffer interface for executing render, surface, and compute passes.
 *
 * This file declares the CommandBuffer abstract base class, which provides
 * virtual methods for starting various types of rendering passes and submitting
 * encoded commands to the GPU.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __PASS_RENDERER_HPP__
#define __PASS_RENDERER_HPP__

#include <handle.hpp>
#include <span.hpp>
#include <resources/Buffer.hpp>
#include <resources/texture.hpp>
#include <render/commands.hpp>

namespace gfx
{
    /**
     * @brief Interface for recording and submitting GPU commands.
     *
     * A CommandBuffer provides methods for beginning specific types of passes:
     * - Render passes for standard drawing.
     * - Surface passes for direct rendering to swapchain images or surfaces.
     * - Compute passes for running compute shaders that write to textures or buffers.
     *
     * The encoded commands must be finalized by calling Submit().
     */
    class CommandBuffer
    {
    public:
        /**
         * @brief Begins a render pass.
         *
         * @param renderPass Handle to the RenderPass resource that describes
         *                   the attachments and pipeline state.
         * @param drawCalls  Encoded draw command stream (from DrawStreamEncoder).
         */
        virtual void BeginRenderPass(
            const RenderDescriptor&& desc,
            utils::Span<uint32_t> drawCalls
        ) = 0;

        /**
         * @brief Begins a compute pass.
         *
         * @param textureWrite List of textures that will be written to by the compute shaders.
         * @param bufferWrite  List of buffers that will be written to by the compute shaders.
         * @param dispatches   List of compute dispatch commands to execute.
         */
        virtual void BeginComputePass(
            utils::Span<utils::Handle<Texture>> textureWrite,
            utils::Span<utils::Handle<Buffer>> bufferWrite,
            utils::Span<Dispatch> dispatches
        ) = 0;
    };
}

#endif // __PASS_RENDERER_HPP__
