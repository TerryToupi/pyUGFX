#ifndef __VULKAN_DEVICE_HPP__
#define __VULKAN_DEVICE_HPP__

#include <device.hpp>

namespace gfx
{
	class VulkanDevice final : public Device
	{
		virtual void Init() override;
		virtual void ShutDown() override;
	};
}

#endif