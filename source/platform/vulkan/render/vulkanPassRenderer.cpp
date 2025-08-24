/// \cond

#include <resources/vulkanResourceManger.hpp>
#include <render/vulkanPassRenderer.hpp>
#include <render/vulkanRenderer.hpp>
#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>

void gfx::VulkanCommandBuffer::BeginRenderPass(const RenderPassCommand&& cmd, utils::Span<uint32_t> drawCalls)
{
	GFX_ASSERT(m_State == gfx::CommandBufferState::CAPTURED);

	VulkanWindow* window = static_cast<VulkanWindow*>(gfx::Window::instance.get());
	VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());
	VulkanResourceManager* rm = static_cast<VulkanResourceManager*>(gfx::ResourceManager::instance.get());

	VkRenderingInfoKHR renderingInfo = {};
	renderingInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;

	unsigned maxColors = 0;
	VkRenderingAttachmentInfoKHR clsAttachments[8];
	{
		for (const auto& clr : cmd.colorTargets)
		{
			if (clr.isSwapChain)
			{
				clsAttachments[maxColors].pNext = nullptr;
				clsAttachments[maxColors].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
				clsAttachments[maxColors].loadOp = gfx::DecodeLoadOperationType(clr.loadOp);
				clsAttachments[maxColors].storeOp = gfx::DecodeStoreOperationType(clr.storeOp);
				clsAttachments[maxColors].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				clsAttachments[maxColors].clearValue = VkClearValue{};
				clsAttachments[maxColors].imageView = window->GetCurrentSwapChainImageView();
				clsAttachments[maxColors].resolveMode = VK_RESOLVE_MODE_NONE; // unless doing MSAA
				clsAttachments[maxColors].resolveImageView = VK_NULL_HANDLE;
				clsAttachments[maxColors].resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				++maxColors;
			}
			else
			{
				clsAttachments[maxColors].pNext = nullptr;
				clsAttachments[maxColors].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
				clsAttachments[maxColors].loadOp = gfx::DecodeLoadOperationType(clr.loadOp);
				clsAttachments[maxColors].storeOp = gfx::DecodeStoreOperationType(clr.storeOp);
				clsAttachments[maxColors].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				clsAttachments[maxColors].clearValue = VkClearValue{};
				clsAttachments[maxColors].imageView = VK_NULL_HANDLE;
				clsAttachments[maxColors].resolveMode = VK_RESOLVE_MODE_NONE; // unless doing MSAA
				clsAttachments[maxColors].resolveImageView = VK_NULL_HANDLE;
				clsAttachments[maxColors].resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				++maxColors;
			}
		}

		renderingInfo.colorAttachmentCount = maxColors;
		renderingInfo.pColorAttachments = clsAttachments;
	}

	VkRenderingAttachmentInfoKHR depthAttachment = {};
	{
		if (cmd.depthTarget.enabled)
		{
			depthAttachment.loadOp = gfx::DecodeLoadOperationType(cmd.depthTarget.loadOp);
			depthAttachment.storeOp = gfx::DecodeStoreOperationType(cmd.depthTarget.storeOp);
			depthAttachment.imageLayout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR;
			depthAttachment.clearValue = VkClearValue{};
			depthAttachment.imageView = VK_NULL_HANDLE;

			renderingInfo.pDepthAttachment = &depthAttachment;
		}
		else
		{
			renderingInfo.pDepthAttachment = VK_NULL_HANDLE;
		}
	}

	renderingInfo.layerCount = 1;
	renderingInfo.renderArea = VkRect2D{ VkOffset2D{}, VkExtent2D{800, 600} };

	vkCmdBeginRenderingKHR(m_CommandBuffer, &renderingInfo);

	vkCmdEndRenderingKHR(m_CommandBuffer);

	//VkImageMemoryBarrier barrier{};
	//barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	//barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	//barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	//barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	//barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	//barrier.image = window->GetCurrentSwapChainImage();
	//barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	//barrier.subresourceRange.baseMipLevel = 0;
	//barrier.subresourceRange.levelCount = 1;
	//barrier.subresourceRange.baseArrayLayer = 0;
	//barrier.subresourceRange.layerCount = 1;

	//// src/dst stage masks depend on usage — here it's just a "dummy" transition
	//barrier.srcAccessMask = 0;
	//barrier.dstAccessMask = 0;

	//vkCmdPipelineBarrier(
	//	m_CommandBuffer,
	//	VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,  // earliest possible
	//	VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, // latest possible
	//	0,
	//	0, nullptr,
	//	0, nullptr,
	//	1, &barrier
	//);

	m_State = gfx::CommandBufferState::PENDING_UPLOAD;
}

void gfx::VulkanCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, utils::Span<Dispatch> dispatches)
{
}

void gfx::VulkanCommandBuffer::Submit()
{
	//GFX_ASSERT(m_State == gfx::CommandBufferState::PENDING_UPLOAD);
	VulkanRenderer* renderer = static_cast<VulkanRenderer*>(gfx::Renderer::instance.get());

	VK_CHECK(vkEndCommandBuffer(m_CommandBuffer), "vkEndCommandBuffer");

	VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	VkSubmitInfo submitInfo =
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.pNext = nullptr,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &m_WaitSemaphore,
		.pWaitDstStageMask = &waitStage,
		.commandBufferCount = 1,
		.pCommandBuffers = &m_CommandBuffer,
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &m_SignalSemaphore,
	};

	VK_CHECK(vkQueueSubmit(renderer->GetGraphicsQueue(), 1, &submitInfo, m_Fence), "vkQueueSubmit");

	m_State = gfx::CommandBufferState::UPLOADED;
}

/// \endcond
