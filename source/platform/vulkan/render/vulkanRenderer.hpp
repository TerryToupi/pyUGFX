/// \cond

#ifndef __VULKAN_RENDERER_HPP__
#define __VULKAN_RENDERER_HPP__

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

        virtual CommandBuffer* BeginCommandRecording(gfx::CommandBufferType type) override;

		void BeginFrame();
		void EndFrame();

		VkQueue GetGraphicsQueue();
		VkQueue GetPresentQueue();

		VkSemaphore GetImageAvailableSemaphore();
		VkSemaphore GetMainBufferSemaphore();
		VkSemaphore GetUIBufferSemaphore();

	private: 
		void CreateSyncStructures();
		void CreateCommands();

	private:
		// queues
		VkQueue m_GraphicsQueue;
		VkQueue m_PresentQueue;

		// fences
		VkFence m_GraphicsFence;

		// Semaphores
		VkSemaphore m_ImageAvailableSemaphore;
		VkSemaphore m_MainBufferSemaphore;
		VkSemaphore m_UIBufferSemaphore;

		// command buffers
		VkCommandPool m_CommandPool;
		VulkanCommandBuffer m_MainBuffer;
		VulkanCommandBuffer m_UIBuffer;
	};
}

#endif

/// \endcond