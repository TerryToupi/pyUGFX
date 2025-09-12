/// \cond

#ifndef __VULKAN_RENDERER_HPP__
#define __VULKAN_RENDERER_HPP__

#include <vector>
#include <array>
#include <vulkanCommon.hpp>
#include <render/renderer.hpp>
#include <render/vulkanPassRenderer.hpp>

namespace gfx
{
	class VulkanRenderer : public Renderer
	{
	public:
        virtual void Init() override;
        virtual void ShutDown() override;

		bool BeginFrame();
		void EndFrame();

        virtual CommandBuffer* BeginCommandRecording() override;

	private:
		void CreateFrameSubmission(uint32_t maxFramesInFlight);

	private: 
		struct FrameData
		{
			gfx::VulkanCommandBuffer cmdBuffer;
			uint64_t frameNumber;
		};
		std::vector<FrameData> m_frameData{};
		VkSemaphore m_frameTimelineSemaphore{};
		uint32_t	m_frameRingCurrent{ 0 };
	};
}

#endif

/// \endcond