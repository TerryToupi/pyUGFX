/// \cond

#include <render/vulkanPassRenderer.hpp>
#include <render/vulkanRenderer.hpp>
#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>

void gfx::VulkanCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Span<uint32_t> drawCalls)
{
	VulkanWindow* window = static_cast<VulkanWindow*>(gfx::Window::instance.get());

	GFX_ASSERT(m_State == gfx::CommandBufferState::CAPTURED);

	VkImageMemoryBarrier barrier{};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = window->GetCurrentSwapChainImage();
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	// src/dst stage masks depend on usage — here it's just a "dummy" transition
	barrier.srcAccessMask = 0;
	barrier.dstAccessMask = 0;

	vkCmdPipelineBarrier(
		m_CommandBuffer,
		VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,  // earliest possible
		VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, // latest possible
		0,
		0, nullptr,
		0, nullptr,
		1, &barrier
	);

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
