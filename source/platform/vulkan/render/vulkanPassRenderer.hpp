/// \cond

#ifndef __VULKAN_PASS_RENDERER_HPP__
#define __VULKAN_PASS_RENDERER_HPP__

#include <render/passRenderer.hpp>
#include <vulkanEnums.hpp>
#include <vulkanCommon.hpp>

namespace gfx
{
	class VulkanCommandBuffer : public CommandBuffer
	{
	public:
        virtual void BeginRenderPass(
            utils::Handle<RenderPass> renderPass,
            utils::Span<uint32_t> drawCalls
        ) override;

        virtual void BeginComputePass(
            utils::Span<utils::Handle<Texture>> textureWrite,
            utils::Span<utils::Handle<Buffer>> bufferWrite,
            utils::Span<Dispatch> dispatches
        ) override;

        virtual void Submit() override;

	private:
        VkFence m_Fence = VK_NULL_HANDLE;
        VkSemaphore m_WaitSemaphore = VK_NULL_HANDLE;
        VkSemaphore m_SignalSemaphore = VK_NULL_HANDLE;
		VkCommandBuffer m_CommandBuffer = VK_NULL_HANDLE;

        gfx::CommandBufferState m_State = gfx::CommandBufferState::EMPTY;

		friend class VulkanRenderer;
	};
}

#endif

/// \endcond
