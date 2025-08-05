#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <common.hpp>
#include <enums.hpp>
#include <render/passRenderer.hpp>

namespace gfx
{
	class Renderer
	{
	public:
		static inline sPtr<Renderer> instance = nullptr;

		virtual void Init() = 0;
		virtual void ShutDown() = 0;

		virtual CommandBuffer* BeginCommandRecording(gfx::CommandBufferType type) = 0;
	};
}

#endif
