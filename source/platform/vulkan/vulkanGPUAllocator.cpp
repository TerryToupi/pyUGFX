#include <VulkanGPUAllocator.hpp>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

#include <vulkanDevice.hpp>

void gfx::VulkanGPUAllocator::Init()
{
	gfx::VulkanDevice* dImpl = static_cast<gfx::VulkanDevice*>(gfx::Device::instance.get());

	VmaVulkanFunctions vulkanFunctions = {};
	vulkanFunctions.vkGetInstanceProcAddr = vkGetInstanceProcAddr;
	vulkanFunctions.vkGetDeviceProcAddr = vkGetDeviceProcAddr;

	VmaAllocatorCreateInfo allocatorInfo = {};
	allocatorInfo.instance = dImpl->GetInstance();
	allocatorInfo.physicalDevice = dImpl->GetAdapter();
	allocatorInfo.pVulkanFunctions = &vulkanFunctions;
	allocatorInfo.device = dImpl->GetDevice();

	vmaCreateAllocator(&allocatorInfo, &m_Allocator);
}

void gfx::VulkanGPUAllocator::ShutDown()
{
	vmaDestroyAllocator(m_Allocator);
}

void gfx::VulkanGPUAllocator::BindBufferToAllocation(VkBuffer& buffer, VulkanMemoryAllocation& alloc)
{
	vmaBindBufferMemory(m_Allocator, alloc.m_Allocation, buffer);
}

gfx::VulkanMemoryAllocation gfx::VulkanGPUAllocator::CreateAllocation(const VkMemoryRequirements& memReq, const VmaAllocationCreateInfo& createInfo)
{
	VmaAllocation alloc;
	VmaAllocationInfo info;

	vmaAllocateMemory(m_Allocator, &memReq, &createInfo, &alloc, &info);

	return { alloc, info };
}

gfx::VulkanMemoryAllocation gfx::VulkanGPUAllocator::CreateAllocationForBuffer(const VkBufferCreateInfo& bufferReq, VkBuffer* buffer, const VmaAllocationCreateInfo& createInfo)
{
	VmaAllocation alloc;
	VmaAllocationInfo info;

	vmaCreateBuffer(m_Allocator, &bufferReq, &createInfo, buffer, &alloc, &info);

	return { alloc, info };
}

gfx::VulkanMemoryAllocation gfx::VulkanGPUAllocator::CreateAllocationForTexture(const VkImageCreateInfo& textReq, VkImage* image, const VmaAllocationCreateInfo& createInfo)
{
	VmaAllocation alloc;
	VmaAllocationInfo info;

	vmaCreateImage(m_Allocator, &textReq, &createInfo, image, &alloc, &info);

	return { alloc, info };
}

void gfx::VulkanGPUAllocator::RemoveAllocation(VulkanMemoryAllocation& alloc)
{
	if (alloc.m_Allocation != VK_NULL_HANDLE)
		vmaFreeMemory(m_Allocator, alloc.m_Allocation);

	alloc.m_Allocation = VK_NULL_HANDLE;
	alloc.m_Info = {};
}


