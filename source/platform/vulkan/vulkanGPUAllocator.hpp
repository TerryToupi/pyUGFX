/// \cond

#include <common.hpp>
#include <vulkanCommon.hpp>
#include <resources/vulkanMemAllocation.hpp>

namespace gfx
{
	class VulkanGPUAllocator
	{
	public:
		static inline sPtr<VulkanGPUAllocator> instance;

		void Init();
		void ShutDown();

		void BindBufferToAllocation(VkBuffer& buffer, VulkanMemoryAllocation& alloc);

		VulkanMemoryAllocation CreateAllocation(const VkMemoryRequirements& memReq, const VmaAllocationCreateInfo& createInfo);
		VulkanMemoryAllocation CreateAllocationForBuffer(const VkBufferCreateInfo& bufferReq, VkBuffer* buffer, const VmaAllocationCreateInfo& createInfo);
		VulkanMemoryAllocation CreateAllocationForTexture(const VkImageCreateInfo& textReq, VkImage* image, const VmaAllocationCreateInfo& createInfo);

		void RemoveAllocation(VulkanMemoryAllocation& alloc);

	private:
		VmaAllocator m_Allocator;
	};
}

/// \endcond