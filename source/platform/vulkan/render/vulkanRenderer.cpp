/// \cond

#include <render/vulkanRenderer.hpp>
#include <vulkanDevice.hpp>

void gfx::VulkanRenderer::Init()
{
	gfx::VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());

	vkGetDeviceQueue(device->GetDevice(), device->GetQueueIndicies().graphicsFamily.value(), 0, &m_GraphicsQueue);
	vkGetDeviceQueue(device->GetDevice(), device->GetQueueIndicies().presentFamily.value(), 0, &m_PresentQueue);

	CreateSyncStructures();
	CreateCommands();
}

void gfx::VulkanRenderer::ShutDown()
{
	VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());

	vkDeviceWaitIdle(device->GetDevice());

	vkDestroyFence(device->GetDevice(), m_GraphicsFence, nullptr);
	vkDestroySemaphore(device->GetDevice(), m_ImageAvailableSemaphore, nullptr);
	vkDestroySemaphore(device->GetDevice(), m_MainBufferSemaphore, nullptr);
	vkDestroySemaphore(device->GetDevice(), m_UIBufferSemaphore, nullptr);
	vkDestroyCommandPool(device->GetDevice(), m_CommandPool, nullptr);
}

gfx::CommandBuffer* gfx::VulkanRenderer::BeginCommandRecording(gfx::CommandBufferType type)
{
	switch (type)
	{
	case gfx::CommandBufferType::OFFSCREEN:
		break;
	case gfx::CommandBufferType::MAIN:
		if (m_MainBuffer.m_State == gfx::CommandBufferState::EMPTY)
		{
			m_MainBuffer.m_State = gfx::CommandBufferState::CAPTURED;
			return static_cast<gfx::CommandBuffer*>(&m_MainBuffer);
		}
		break;
	case gfx::CommandBufferType::POST:
		break;
	case gfx::CommandBufferType::UI:
		if (m_UIBuffer.m_State == gfx::CommandBufferState::EMPTY)
		{
			m_UIBuffer.m_State = gfx::CommandBufferState::CAPTURED;
			return static_cast<gfx::CommandBuffer*>(&m_UIBuffer);
		}
		break;
	default:
		 
		break;
	}
}

void gfx::VulkanRenderer::BeginFrame()
{
	gfx::VulkanDevice* device = static_cast<gfx::VulkanDevice*>(gfx::Device::instance.get());

	VK_CHECK(vkWaitForFences(device->GetDevice(), 1, &m_GraphicsFence, true, 1000000000), "vkWaitForFences");
	VK_CHECK(vkResetFences(device->GetDevice(), 1, &m_GraphicsFence), "vkResetFences");
}

void gfx::VulkanRenderer::EndFrame()
{
	if (m_MainBuffer.m_State == gfx::CommandBufferState::EMPTY)
		m_MainBuffer.Submit();
	if (m_UIBuffer.m_State == gfx::CommandBufferState::EMPTY)
		m_UIBuffer.Submit();

	m_MainBuffer.m_State = gfx::CommandBufferState::EMPTY;
	m_UIBuffer.m_State = gfx::CommandBufferState::EMPTY;
}

VkQueue gfx::VulkanRenderer::GetGraphicsQueue()
{
	return m_GraphicsQueue;
}

VkQueue gfx::VulkanRenderer::GetPresentQueue()
{
	return m_PresentQueue;
}

VkSemaphore gfx::VulkanRenderer::GetImageAvailableSemaphore()
{
	return m_ImageAvailableSemaphore;
}

VkSemaphore gfx::VulkanRenderer::GetMainBufferSemaphore()
{
	return m_MainBufferSemaphore;
}

VkSemaphore gfx::VulkanRenderer::GetUIBufferSemaphore()
{
	return m_UIBufferSemaphore;
}

void gfx::VulkanRenderer::CreateSyncStructures()
{
	VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());

	VkFenceCreateInfo fenceCreateInfo =
	{
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT,
	};
	VkSemaphoreCreateInfo semaphoreCreateInfo =
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
	};

	VK_CHECK(vkCreateFence(device->GetDevice(), &fenceCreateInfo, nullptr, &m_GraphicsFence), "vkCreateFence");

	VK_CHECK(vkCreateSemaphore(device->GetDevice(), &semaphoreCreateInfo, nullptr, &m_ImageAvailableSemaphore), "vkCreateSemaphore");
	VK_CHECK(vkCreateSemaphore(device->GetDevice(), &semaphoreCreateInfo, nullptr, &m_MainBufferSemaphore), "vkCreateSemaphore");
	VK_CHECK(vkCreateSemaphore(device->GetDevice(), &semaphoreCreateInfo, nullptr, &m_UIBufferSemaphore), "vkCreateSemaphore");
}

void gfx::VulkanRenderer::CreateCommands()
{
	VulkanDevice* device = static_cast<VulkanDevice*>(gfx::Device::instance.get());

	const QueueFamilyIndices& indices = device->GetQueueIndicies();

	VkCommandPoolCreateInfo commandPoolInfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.pNext = nullptr,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = indices.graphicsFamily.value(),
	};

	VK_CHECK(vkCreateCommandPool(device->GetDevice(), &commandPoolInfo, nullptr, &m_CommandPool), "vkCreateCommandPool");

	VkCommandBuffer commandBuffers[2];
	VkCommandBufferAllocateInfo cmdAllocInfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = nullptr,
		.commandPool = m_CommandPool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 2,
	};
	VK_CHECK(vkAllocateCommandBuffers(device->GetDevice(), &cmdAllocInfo, commandBuffers), "vkAllocateCommandBuffers");

	m_MainBuffer.m_CommandBuffer = commandBuffers[0];
	m_MainBuffer.m_Fence = m_GraphicsFence;
	m_MainBuffer.m_WaitSemaphore = m_ImageAvailableSemaphore;
	m_MainBuffer.m_SignalSemaphore = m_MainBufferSemaphore;

	m_UIBuffer.m_CommandBuffer = commandBuffers[1];
	m_UIBuffer.m_Fence = m_GraphicsFence;
	m_UIBuffer.m_WaitSemaphore = m_MainBufferSemaphore;
	m_UIBuffer.m_SignalSemaphore = m_ImageAvailableSemaphore;
}

/// \endcond

