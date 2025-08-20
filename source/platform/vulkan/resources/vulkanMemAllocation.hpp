/// \cond

#ifndef __VULKAN_MEMORY_ALLOCATION__
#define __VULKAN_MEMORY_ALLOCATION__

#include <vma/vk_mem_alloc.h>

namespace gfx
{
	class VulkanMemoryAllocation
	{
	public:
		VulkanMemoryAllocation(VmaAllocation alloc, VmaAllocationInfo info);

		const char* GetName();
		void* GetMappedRange();
		void* GetUserData();
		uint32_t GetMemType();

	private:
		VmaAllocation m_Allocation = VK_NULL_HANDLE;
		VmaAllocationInfo m_Info = {};

		friend class VulkanGPUAllocator;
	};
}

#endif // !__VULKAN_MEMORY_ALLOCATION__


/// \endcond