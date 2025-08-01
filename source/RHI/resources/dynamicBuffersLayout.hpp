#ifndef __DYNAMIC_BUFFERS_LAYOUT_HPP__
#define __DYNAMIC_BUFFERS_LAYOUT_HPP__ 

#include <span.hpp>
#include <handle.hpp>
#include <enums.hpp>

namespace gfx
{
	class DynamicBuffersLayout;

	struct DynamicBuffersLayoutDescriptor
	{
        struct BufferBinding
        {
            uint32_t slot = 0;
            BufferBindingType type = BufferBindingType::UNIFORM;
            ShaderStage visibility = ShaderStage::VERTEX | ShaderStage::FRAGMENT;
            uint32_t byteOffset = 0;
            uint32_t range = 0;
        };
        utils::Span<BufferBinding> bufferBindings;
	};
}

#endif // !__BIND_GROUP_LAYOUT_HPP__
