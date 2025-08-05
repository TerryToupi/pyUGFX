#ifndef __METAL_DEVICE_HPP__
#define __METAL_DEVICE_HPP__

#include <device.hpp>

namespace gfx
{
	class MetalDevice final : public Device
	{
		virtual void Init() override;
		virtual void ShutDown() override;
	};
}

#endif