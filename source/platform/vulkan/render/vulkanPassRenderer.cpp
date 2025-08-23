/// \cond

#include <render/vulkanPassRenderer.hpp>
#include <render/vulkanRenderer.hpp>

void gfx::VulkanCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Span<uint32_t> drawCalls)
{
	GFX_ASSERT(m_State == gfx::CommandBufferState::CAPTURED);

	// Now that we are sure that the commands finished executing, we can safely reset the command buffer to begin recording again.
	VK_CHECK(vkResetCommandBuffer(m_CommandBuffer, 0), "vkResetCommandBuffer");

	// Begin the command buffer recording. We will use this command buffer exactly once, so we want to let Vulkan know that
	VkCommandBufferBeginInfo cmdBeginInfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.pInheritanceInfo = nullptr,
	};

	VK_CHECK(vkBeginCommandBuffer(m_CommandBuffer, &cmdBeginInfo), "vkBeginCommandBuffer");

	m_State = gfx::CommandBufferState::PENDING_UPLOAD;
}

void gfx::VulkanCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, utils::Span<Dispatch> dispatches)
{
}

void gfx::VulkanCommandBuffer::Submit()
{
	//GFX_ASSERT(m_State == gfx::CommandBufferState::PENDING_UPLOAD);
	VulkanRenderer* renderer = static_cast<VulkanRenderer*>(gfx::Renderer::instance.get());

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
