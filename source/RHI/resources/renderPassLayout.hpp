#ifndef __RENDER_PASS_LAYOUT_HPP__
#define __RENDER_PASS_LAYOUT_HPP__

#include <span.hpp>
#include <enums.hpp>

namespace gfx
{
    class RenderPassLayout;
    
    struct RenderPassLayoutDescriptor
    {
        struct DepthDescriptor
        {
            bool depthTarget = false;
            TextureFormat depthTargetFormat = TextureFormat::D32_FLOAT;
        };
        
        struct ColorTargetDescriptor
        {
            bool enabled = true;
            TextureFormat format = TextureFormat::RGBA8_UNORM;
        };

        struct SubPass
        {
            DepthDescriptor depth;
            utils::Span<ColorTargetDescriptor> colorTargets;
        };
        
        utils::Span<SubPass> subPasses;
    };
}

#endif
