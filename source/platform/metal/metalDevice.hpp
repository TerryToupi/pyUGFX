#ifndef __METAL_DEVICE_HPP__
#define __METAL_DEVICE_HPP__

#include <device.hpp>
#include <metalGlue.hpp>

namespace gfx
{
	class MetalDevice final : public Device
	{
    public:
		virtual void Init() override;
		virtual void ShutDown() override;
        
        MTL::Device* GetDevice();
        
    private:
        MTL::Device* m_Device;
	};
}

#endif
