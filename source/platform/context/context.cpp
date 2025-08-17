/// \cond

#include <context.hpp>
#include <log.hpp>

#include <device.hpp>
#include <window.hpp>

#if PYUGFX_ENABLE_VULKAN
#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>
#include <resources/vulkanResourceManger.hpp>

static void VulkanInit()
{
    gfx::Window::instance = gfx::CreateShared<gfx::VulkanWindow>();
    gfx::Device::instance = gfx::CreateShared<gfx::VulkanDevice>();
    gfx::ResourceManager::instance = gfx::CreateShared<gfx::VulkanResourceManager>();

    gfx::Window::instance->Init({
        .name = "Heavy",
        .width = 800,
        .height = 600,
    });
    gfx::Device::instance->Init();
    gfx::ResourceManager::instance->Init();
}
#endif

#if PYUGFX_ENABLE_METAL
#include <metalDevice.hpp>
#include <metalWindow.hpp>
#include <resources/metalResourceManger.hpp>

static void MetalInit()
{
    gfx::Window::instance = gfx::CreateShared<gfx::MetalWindow>();
    gfx::Device::instance = gfx::CreateShared<gfx::MetalDevice>();
    gfx::ResourceManager::instance = gfx::CreateShared<gfx::MetalResourceManager>();

    gfx::Window::instance->Init({
        .name = "Heavy",
        .width = 800,
        .height = 600,
    });
    gfx::Device::instance->Init();
    gfx::ResourceManager::instance->Init();
}
#endif

void setup::ContextShutDown()
{
    gfx::ResourceManager::instance->ShutDown();
    gfx::Window::instance->ShutDown();
	gfx::Device::instance->ShutDown();

    gfx::ResourceManager::instance.reset();
    gfx::Window::instance.reset();
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
        #if PYUGFX_ENABLE_VULKAN && defined(_WIN64)
        {
            GFX_TRACE("Win32 platform detected, Initializing Vulkan API!");
            VulkanInit();
            return;
        }
        #endif

        #if PYUGFX_ENABLE_METAL && defined(__APPLE__)
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

/// \endcond
