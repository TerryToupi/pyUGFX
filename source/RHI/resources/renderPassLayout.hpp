/**
 * @file renderPassLayout.hpp
 * @brief Defines RenderPassLayout and its descriptor structures.
 *
 * This file provides structures to describe the layout of a render pass,
 * including depth and color target formats and subpass configuration.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __RENDER_PASS_LAYOUT_HPP__
#define __RENDER_PASS_LAYOUT_HPP__

#include <span.hpp>
#include <enums.hpp>

namespace gfx
{
    class RenderPassLayout;

    /**
     * @brief Descriptor for creating a RenderPassLayout.
     *
     * Contains information about subpasses and their associated depth
     * and color targets.
     */
    struct RenderPassLayoutDescriptor
    {
        /**
         * @brief Descriptor for a depth attachment.
         */
        struct DepthDescriptor
        {
            /// Whether the depth target is enabled.
            bool depthTarget = false;

            /// Format of the depth target texture.
            TextureFormat depthTargetFormat = TextureFormat::D32_FLOAT;
        };

        /**
         * @brief Descriptor for a color attachment.
         */
        struct ColorTargetDescriptor
        {
            /// Whether this color target is enabled.
            bool enabled = true;

            /// Format of the color target texture.
            TextureFormat format = TextureFormat::RGBA8_UNORM;
        };

        /**
         * @brief Describes a single subpass in the render pass layout.
         */
        struct SubPass
        {
            /// Depth attachment for this subpass.
            DepthDescriptor depth;

            /// Span of color attachments for this subpass.
            utils::Span<ColorTargetDescriptor> colorTargets;
        };

        /// Span of subpasses for this render pass layout.
        utils::Span<SubPass> subPasses;
    };
}

#endif // !__RENDER_PASS_LAYOUT_HPP__
