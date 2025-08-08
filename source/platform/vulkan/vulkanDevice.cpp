#include <vulkanDevice.hpp>
#include <assert.hpp>
#include <Volk/volk.h>

void gfx::VulkanDevice::Init()
{
	GFX_TRACE("[Vulkan] Attempting to initialize vulkan meta laoder!");
	GFX_ASSERT(volkInitialize() == VK_SUCCESS);
}

void gfx::VulkanDevice::ShutDown()
{
}
