#ifndef __DYNAMIC_BUFFER_HPP__
#define __DYNAMIC_BUFFER_HPP__

#include <enums.hpp>
#include <handle.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffersLayout.hpp>

namespace gfx
{
	class DynamicBuffers;

	struct DynamicBuffersDescriptor
	{
		utils::Handle<DynamicBuffersLayout> dynamicBuffersLayout;

		struct BufferEntry
        {
            uint32_t slot = 0;
            utils::Handle<Buffer> buffer;
			uint32_t byteOffset = 0;
            uint32_t range = 0;
        };
        utils::Span<BufferEntry> buffers;
	};
}

#endif // !__DYNAMIC_BUFFER_HPP__
