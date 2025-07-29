#ifndef __SHADER_HPP__ 
#define __SHADER_HPP__ 

#include <string>

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>
#include <resources/bindGroupLayout.hpp>
#include <resources/renderPassLayout.hpp>

namespace gfx
{
	class Shader; 

	struct ShaderDescriptor
	{
		struct ShaderStage 
		{
			bool enabled = true;
			utils::Span<uint8_t> sourceCode;
			std::string entryFunc;         // Entry function name
		};

		struct VertexAttribute 
		{
			uint32_t byteOffset;
			gfx::VertexFormat format;
		};

		struct VertexBufferBinding 
		{
			uint32_t byteStride;
			utils::Span<VertexAttribute> attributes;
		};

		struct GraphicsState 
		{
            gfx::Compare depthTest = gfx::Compare::UNDEFINED;
			utils::Span<VertexBufferBinding> vertexBufferBindings;
			utils::Handle<RenderPassLayout> renderPassLayout;
		};

		ShaderPipelineType type = ShaderPipelineType::GRAPHICS;
		ShaderStage VS; // Vertex Shader
		ShaderStage PS; // Pixel Shader
		utils::Span<utils::Handle<BindGroupLayout>> bindLayouts;
		GraphicsState graphicsState;
	};
}

#endif // !__SHADER_HPP__ 
