/**
 * @file shader.hpp
 * @brief Defines GPU shader resource and its creation descriptor.
 *
 * Shaders define programmable stages of the GPU pipeline, including vertex
 * and fragment stages, input layouts, blend operations, and associated bind groups.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>
#include <resources/bindGroupLayout.hpp>

namespace gfx
{
    /**
     * @brief Represents a GPU shader resource.
     */
    class Shader;

    /**
     * @brief Descriptor for creating a GPU shader.
     */
    struct ShaderDescriptor
    {
        /**
         * @brief Represents a single programmable shader stage (vertex, fragment, etc.)
         */
        struct ShaderStage
        {
            bool enabled = false;                 ///< Whether this stage is active.
            utils::Span<uint8_t> sourceCode;     ///< SPIR-V or native bytecode for the stage.
            std::string entryFunc;               ///< Name of the entry point function.
        };

        /**
         * @brief Defines a vertex attribute layout.
         */
        struct VertexAttribute
        {
            uint32_t byteOffset;                  ///< Byte offset of the attribute in the vertex.
            gfx::VertexFormat format;             ///< Data format of the attribute.
        };

        /**
         * @brief Defines a vertex buffer binding layout.
         */
        struct VertexBufferBinding
        {
            uint32_t byteStride;                  ///< Stride between consecutive vertices.
            utils::Span<VertexAttribute> attributes; ///< Attributes contained in this buffer.
        };

        /**
         * @brief Describes blending operations for a render target.
         */
        struct BlendDescriptor
        {
            BlendOperation colorOp = BlendOperation::ADD;           ///< Color blending operation.
            BlendFactor srcColorFactor = BlendFactor::SRC_ALPHA;   ///< Source color factor.
            BlendFactor dstColorFactor = BlendFactor::ONE_MINUS_SRC_ALPHA; ///< Destination color factor.
            BlendOperation alphaOp = BlendOperation::ADD;          ///< Alpha blending operation.
            BlendFactor srcAlphaFactor = BlendFactor::ONE;         ///< Source alpha factor.
            BlendFactor dstAlphaFactor = BlendFactor::ZERO;        ///< Destination alpha factor.
        };

        /**
         * @brief Graphics pipeline state for this shader.
         */
        struct GraphicsState
        {
            gfx::Compare depthTest = gfx::Compare::UNDEFINED;               ///< Depth test function.
            utils::Span<VertexBufferBinding> vertexBufferBindings;          ///< Vertex buffer layout.
            BlendDescriptor blend = {};                                      ///< Blending settings.
        };

        ShaderPipelineType type = ShaderPipelineType::GRAPHICS;             ///< Shader pipeline type.
        ShaderStage VS;                                                      ///< Vertex shader stage.
        ShaderStage PS;                                                      ///< Pixel (fragment) shader stage.
        utils::Span<utils::Handle<BindGroupLayout>> bindLayouts;             ///< Bind group layouts used by shader.
        GraphicsState graphicsState;                                         ///< Graphics pipeline state.
    };
}

#endif // !__SHADER_HPP__
