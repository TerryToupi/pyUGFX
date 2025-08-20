#include <resources/vulkanMemAllocation.hpp>

gfx::VulkanMemoryAllocation::VulkanMemoryAllocation(VmaAllocation alloc, VmaAllocationInfo info)
{
	m_Allocation = alloc;
	m_Info = info;
}

const char* gfx::VulkanMemoryAllocation::GetName()
{
	return m_Info.pName;
}

void* gfx::VulkanMemoryAllocation::GetMappedRange()
{
	return m_Info.pMappedData;
}

void* gfx::VulkanMemoryAllocation::GetUserData()
{
	return m_Info.pUserData;
}

uint32_t gfx::VulkanMemoryAllocation::GetMemType()
{
	return m_Info.memoryType;
}
