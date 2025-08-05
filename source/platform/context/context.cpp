#include <context.hpp>
#include <context/log.hpp>

#include <vulkan/vulkanDevice.hpp>

#include <metal/metalDevice.hpp>

static void VulkanInit()
{
	gfx::Device::instance = gfx::CreateShared<gfx::VulkanDevice>();

	gfx::Device::instance->Init();
}

static void MetalInit()
{
	gfx::Device::instance = gfx::CreateShared<gfx::MetalDevice>();

	gfx::Device::instance->Init();
}

void setup::ContextShutDown()
{
	gfx::Device::instance->ShutDown();

	gfx::Device::instance.reset();

	diag::Logger::ShutDown();
}

void setup::ContextInit(Platforms platform)
{ 
	diag::Logger::Init();

	GFX_TRACE("Logger has been initialized!");

	switch (platform)
	{
	case setup::UNDEFINED:
		{
			#if defined(_WIN64)
			{
				GFX_TRACE("Win32 platform detected, Initializing Vulkan API!");
				VulkanInit();
				return;
			}
			#endif

			#if defined(__APPLE__)
			{
				GFX_TRACE("MacOS platform detected, Initializing Metal API!");
				MetalInit();
				return;
			}
			#endif

			GFX_ERROR("Can't detect OS Platform!");
			exit(1);
		}
		break;

	case setup::VULKAN:
		{
			GFX_TRACE("Initializing Vulkan!");
			VulkanInit();
			return;
		}
		break;

	case setup::METAL:
		{
			GFX_TRACE("Initializing Metal!");
			MetalInit();
			return;
		}
		break;

	default:
		{
			GFX_ERROR("Can't detect OS Platform!");
			exit(1);
		}
		break;
	}
}

