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

		void CreateFrameSubmission(uint32_t maxFramesInFlight);

		bool BeginFrame();
		void EndFrame();

        virtual CommandBuffer* BeginCommandRecording() override;

		VkCommandBuffer BeginSingleTimeCommandRecording();

		void			EndSingleTimeCommandRecording(VkCommandBuffer cmd);

		VkImageMemoryBarrier2 createImageMemoryBarrier(VkImage       image,
														VkImageLayout oldLayout,
														VkImageLayout newLayout,
														VkImageSubresourceRange subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 });

		std::tuple<VkPipelineStageFlags2, VkAccessFlags2> makePipelineStageAccessTuple(VkImageLayout state);

		void cmdTransitionImageLayout(VkCommandBuffer    cmd,
										VkImage            image,
										VkImageLayout      oldLayout,
										VkImageLayout      newLayout,
										VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_COLOR_BIT);

		VkAccessFlags2 inferAccessMaskFromStage(VkPipelineStageFlags2 stage, bool src);

		void cmdBufferMemoryBarrier(VkCommandBuffer       commandBuffer,
									VkBuffer              buffer,
									VkPipelineStageFlags2 srcStageMask,
									VkPipelineStageFlags2 dstStageMask,
									VkAccessFlags2        srcAccessMask = 0,  // Default to infer if not provided
									VkAccessFlags2        dstAccessMask = 0,  // Default to infer if not provided
									VkDeviceSize          offset = 0,
									VkDeviceSize          size = VK_WHOLE_SIZE,
									uint32_t              srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
									uint32_t              dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED);

private:
		void CreateTransientCommandPool();

	private: 
		VkCommandPool m_transientCmdPool{};

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