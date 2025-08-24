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
	if (cmd.swapTarget.enabled)
	{
		clsAttachments[maxColors].pNext = nullptr;
		clsAttachments[maxColors].sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
		clsAttachments[maxColors].loadOp = gfx::DecodeLoadOperationType(cmd.swapTarget.loadOp);
		clsAttachments[maxColors].storeOp = gfx::DecodeStoreOperationType(cmd.swapTarget.storeOp);
		clsAttachments[maxColors].imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		clsAttachments[maxColors].clearValue = VkClearValue{};
		clsAttachments[maxColors].imageView = window->GetCurrentSwapChainImageView();
		clsAttachments[maxColors].resolveMode = VK_RESOLVE_MODE_NONE; // unless doing MSAA
		clsAttachments[maxColors].resolveImageView = VK_NULL_HANDLE;
		clsAttachments[maxColors].resolveImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		++maxColors;
		
		// make the swapchain image as a render target
		TransitionToRenderTarget(window->GetCurrentSwapChainImage());
	}
	else
	{
		for (const auto& clr : cmd.colorTargets)
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
			 
			// make the swapchain image as a render target
			//TransitionToRenderTarget(imageView);
		}
	}
	renderingInfo.colorAttachmentCount = maxColors;
	renderingInfo.pColorAttachments = clsAttachments;

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

	int width = 0, height = 0;
	window->GetWindowSize(&width, &height);

	renderingInfo.layerCount = 1;
	renderingInfo.renderArea = VkRect2D{ VkOffset2D{}, VkExtent2D{(uint32_t)width, (uint32_t)height} };

	vkCmdBeginRenderingKHR(m_CommandBuffer, &renderingInfo);
	{

	}
	vkCmdEndRenderingKHR(m_CommandBuffer);

	if (cmd.swapTarget.enabled)
		TransitionToPresent(window->GetCurrentSwapChainImage());

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

void gfx::VulkanCommandBuffer::TransitionImage(VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout, VkPipelineStageFlags2 srcStage, VkPipelineStageFlags2 dstStage, VkAccessFlags2 srcAccess, VkAccessFlags2 dstAccess)
{
	if (oldLayout == newLayout)
		return; // already in correct layout

	VkImageMemoryBarrier2 barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcStageMask = srcStage;
	barrier.srcAccessMask = srcAccess;
	barrier.dstStageMask = dstStage;
	barrier.dstAccessMask = dstAccess;
	barrier.image = image;
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; // or DEPTH depending on usage
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

	VkDependencyInfo depInfo{};
	depInfo.sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO;
	depInfo.imageMemoryBarrierCount = 1;
	depInfo.pImageMemoryBarriers = &barrier;

	vkCmdPipelineBarrier2(m_CommandBuffer, &depInfo);
}

void gfx::VulkanCommandBuffer::TransitionToRenderTarget(VkImage image)
{
	TransitionImage(
		image, VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		VK_PIPELINE_STAGE_2_NONE, VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
		0, VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT
	);

}

void gfx::VulkanCommandBuffer::TransitionToShaderRead(VkImage image)
{
	TransitionImage(
		image, VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_2_FRAGMENT_SHADER_BIT,
		VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT, VK_ACCESS_2_SHADER_SAMPLED_READ_BIT
	);
}

void gfx::VulkanCommandBuffer::TransitionToPresent(VkImage image)
{
	TransitionImage(
		image, VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
		VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_2_NONE,
		VK_ACCESS_2_COLOR_ATTACHMENT_WRITE_BIT, 0
	);
}

/// \endcond
