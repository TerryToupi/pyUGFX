/// \cond

#include <context.hpp>
#include <log.hpp>

#include <device.hpp>
#include <window.hpp>
#include <resources/resourceManger.hpp>
#include <render/renderer.hpp>

#if PYUGFX_ENABLE_VULKAN
#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>
#include <resources/vulkanResourceManger.hpp>
#include <render/vulkanRenderer.hpp>

static void VulkanInit()
{
    gfx::Device::instance = gfx::CreateShared<gfx::VulkanDevice>();
    gfx::Window::instance = gfx::CreateShared<gfx::VulkanWindow>();
    gfx::ResourceManager::instance = gfx::CreateShared<gfx::VulkanResourceManager>();
    gfx::Renderer::instance = gfx::CreateShared<gfx::VulkanRenderer>();

    gfx::Window::instance->Init({
        .name = "Heavy",
        .width = 800,
        .height = 600,
        .vSync = false
    });
    gfx::Device::instance->Init();
    gfx::Renderer::instance->Init();
    gfx::ResourceManager::instance->Init();

    static_cast<gfx::VulkanWindow*>(gfx::Window::instance.get())->
        swapChain.init();
    static_cast<gfx::VulkanWindow*>(gfx::Window::instance.get())->
        swapChain.initResources(false);
    static_cast<gfx::VulkanRenderer*>(gfx::Renderer::instance.get())->
        CreateFrameSubmission(static_cast<gfx::VulkanWindow*>(gfx::Window::instance.get())->swapChain.getMaxFramesInFlight());
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
    if (gfx::Renderer::instance.get() != nullptr)
        gfx::Renderer::instance->ShutDown();
    if (gfx::ResourceManager::instance.get() != nullptr)
		gfx::ResourceManager::instance->ShutDown();
    if (gfx::Window::instance.get() != nullptr)
		gfx::Window::instance->ShutDown();
    if (gfx::Device::instance.get() != nullptr)
		gfx::Device::instance->ShutDown();

    gfx::Renderer::instance.reset();
    gfx::ResourceManager::instance.reset();
    gfx::Window::instance.reset();
	gfx::Device::instance.reset();
}

void setup::ContextInit(Platforms platform)
{ 
    utils::Logger& logger = utils::Logger::getInstance();
    logger.setLogLevel(utils::Logger::LogLevel::eINFO); 
    logger.setShowFlags(utils::Logger::eSHOW_TIME | utils::Logger::eSHOW_LEVEL);
    logger.setOutputFile("pyUGFX_Logs.txt");
    logger.enableFileOutput(true);

    try
    {
		switch (platform)
		{
		case setup::UNDEFINED:
			#if PYUGFX_ENABLE_VULKAN && defined(_WIN64)
			{
				LOGI("Win32 platform detected, Initializing Vulkan API!");
				VulkanInit();
				return;
			}
			#endif

			#if PYUGFX_ENABLE_METAL && defined(__APPLE__)
			{
				LOGI("MacOS platform detected, Initializing Metal API!");
				MetalInit();
				return;
			}
			#endif

			LOGE("Can't detect OS Platform!");
			exit(1);
			break;

		case setup::VULKAN:
			#if PYUGFX_ENABLE_VULKAN
			{
				LOGI("Initializing Vulkan!");
				VulkanInit();
				return;
			}
			#endif
			break;

		case setup::METAL:
			#if PYUGFX_ENABLE_METAL
			{
				LOGI("Initializing Metal!");
				MetalInit();
				return;
			}
			#endif
			break;

		default:
			LOGE("Can't detect OS Platform!");
			exit(1);
			break;
		}
    }
    catch (const std::exception& e)
    {
        LOGE("%s", e.what());
    }
}

/// \endcond
