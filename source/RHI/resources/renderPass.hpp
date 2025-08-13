/**
 * @file renderPass.hpp
 * @brief Defines RenderPass and its descriptor structures.
 *
 * This file provides structures to describe a render pass, including color
 * and depth targets, clear values, and load/store operations.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __RENDER_PASS_HPP__
#define __RENDER_PASS_HPP__

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>
#include <resources/renderPassLayout.hpp>
#include <resources/texture.hpp>

namespace gfx
{
    class RenderPass;

    /**
     * @brief Descriptor for creating a RenderPass.
     *
     * Contains all necessary information for color and depth attachments,
     * including clear values and load/store operations.
     */
    struct RenderPassDescriptor
    {
        /**
         * @brief Represents a clear color value.
         */
        struct ClearColor
        {
            /// Red component (0.0 - 1.0)
            double r = 0;

            /// Green component (0.0 - 1.0)
            double g = 0;

            /// Blue component (0.0 - 1.0)
            double b = 0;

            /// Alpha component (0.0 - 1.0)
            double a = 0;
        };
        
        /**
         * @brief Represents a single color target attachment.
         */
        struct ColorTarget
        {
            /// Handle to the color texture.
            utils::Handle<Texture> target;

            /// Load operation for the color target.
            LoadOperation loadOp = LoadOperation::CLEAR;

            /// Store operation for the color target.
            StoreOperation storeOp = StoreOperation::STORE;

            /// Clear color to use if loadOp is CLEAR.
            ClearColor clearColor = { 0.2, 0.2, 0.2, 1 };
        };
        
        /**
         * @brief Represents a depth/stencil target attachment.
         */
        struct DepthTarget
        {
            /// Handle to the depth texture.
            utils::Handle<Texture> target;

            /// Load operation for depth.
            LoadOperation loadOp = LoadOperation::CLEAR;

            /// Store operation for depth.
            StoreOperation storeOp = StoreOperation::STORE;

            /// Load operation for stencil.
            LoadOperation stencilLoadOp = LoadOperation::CLEAR;

            /// Store operation for stencil.
            StoreOperation stencilStoreOp = StoreOperation::STORE;

            /// Clear value for depth.
            float clearZ = 0.0f;

            /// Clear value for stencil.
            uint32_t clearStencil = 0;
        };
        
        /// Depth/stencil attachment for this render pass.
        DepthTarget depthTarget;

        /// Span of color targets for this render pass.
        utils::Span<ColorTarget> colorTargets;

        /// Handle to the render pass layout defining pipeline and resource bindings.
        utils::Handle<RenderPassLayout> layout;
    };
}

#endif // !__RENDER_PASS_HPP__
