#include <context.hpp>
#include <log.hpp>

#include <device.hpp>

#if PYUGFX_ENABLE_VULKAN
#include <vulkanDevice.hpp>

static void VulkanInit()
{
    gfx::Device::instance = gfx::CreateShared<gfx::VulkanDevice>();

    gfx::Device::instance->Init();
}
#endif

#if PYUGFX_ENABLE_METAL
#include <metalDevice.hpp>

static void MetalInit()
{
    gfx::Device::instance = gfx::CreateShared<gfx::MetalDevice>();

    gfx::Device::instance->Init();
}
#endif

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
        #if PYUGFX_ENABLE_VULKAN
        {
            GFX_TRACE("Win32 platform detected, Initializing Vulkan API!");
            VulkanInit();
            return;
        }
        #endif

        #if PYUGFX_ENABLE_METAL
        {
            GFX_TRACE("MacOS platform detected, Initializing Metal API!");
            MetalInit();
            return;
        }
        #endif

        GFX_ERROR("Can't detect OS Platform!");
        exit(1);
		break;

	case setup::VULKAN:
        #if PYUGFX_ENABLE_VULKAN
        {
            GFX_TRACE("Initializing Vulkan!");
            VulkanInit();
            return;
        }
        #endif
		break;

	case setup::METAL:
        #if PYUGFX_ENABLE_METAL
        {
			GFX_TRACE("Initializing Metal!");
			MetalInit();
			return;
		}
        #endif
		break;

	default:
        GFX_ERROR("Can't detect OS Platform!");
        exit(1);
		break;
	}
}

