#include <render/vulkanRenderer.hpp>
#include <vulkanDevice.hpp>
#include <vulkanWindow.hpp>

void gfx::VulkanRenderer::Init()
{
    VulkanWindow* windowManager = static_cast<VulkanWindow*>(gfx::Window::instance.get());

    CreateFrameSubmission(windowManager->swapChain.getMaxFramesInFlight());
}

void gfx::VulkanRenderer::ShutDown()
{
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();
        
    VK_CHECK(vkDeviceWaitIdle(device));

    // Frame info
    for (size_t i = 0; i < m_frameData.size(); i++)
    {
        vkFreeCommandBuffers(device, m_frameData[i].cmdBuffer.m_cmdPool, 1, &m_frameData[i].cmdBuffer.m_cmdBuffer);
        vkDestroyCommandPool(device, m_frameData[i].cmdBuffer.m_cmdPool, nullptr);
    }
    vkDestroySemaphore(device, m_frameTimelineSemaphore, nullptr);
}

gfx::CommandBuffer* gfx::VulkanRenderer::BeginCommandRecording()
{
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();

	// Get the frame data for the current frame in the ring buffer
	auto& frame = m_frameData[m_frameRingCurrent];
    ASSERT(frame.cmdBuffer.m_state == gfx::CommandBufferState::EMPTY, "Command buffer was not submited correctly!");

	/*--
	 * Reset the command pool to reuse the command buffer for recording
	 * new rendering commands for the current frame.
	-*/
	VK_CHECK(vkResetCommandPool(device, frame.cmdBuffer.m_cmdPool, 0));
	VkCommandBuffer cmd = frame.cmdBuffer.m_cmdBuffer;

	// Begin the command buffer recording for the frame
	const VkCommandBufferBeginInfo beginInfo{ .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
											 .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };
	VK_CHECK(vkBeginCommandBuffer(cmd, &beginInfo));
    
    frame.cmdBuffer.m_state = gfx::CommandBufferState::CAPTURED;
	return reinterpret_cast<gfx::CommandBuffer*>(&frame.cmdBuffer);
}

void gfx::VulkanRenderer::CreateFrameSubmission(uint32_t maxFramesInFlight)
{
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();
    gfx::QueueInfo queue = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getGraphicsQueue();

    m_frameData.resize(maxFramesInFlight);

    const uint64_t initialValue = (maxFramesInFlight - 1);

    VkSemaphoreTypeCreateInfo timelineCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .pNext = nullptr,
        .semaphoreType = VK_SEMAPHORE_TYPE_TIMELINE,
        .initialValue = initialValue,
    };

    const VkSemaphoreCreateInfo semaphoreCreateInfo{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = &timelineCreateInfo };
    VK_CHECK(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &m_frameTimelineSemaphore));
    DBG_VK_NAME(m_frameTimelineSemaphore);

    const VkCommandPoolCreateInfo cmdPoolCreateInfo{
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .queueFamilyIndex = queue.familyIndex,
    };

    for (uint32_t i = 0; i < maxFramesInFlight; i++)
    {
        m_frameData[i].frameNumber = i;  // Track frame index for synchronization

        // Separate pools allow independent reset/recording of commands while other frames are still in-flight
        VK_CHECK(vkCreateCommandPool(device, &cmdPoolCreateInfo, nullptr, &m_frameData[i].cmdBuffer.m_cmdPool));
        DBG_VK_NAME(m_frameData[i].cmdBuffer.m_cmdPool);

        const VkCommandBufferAllocateInfo commandBufferAllocateInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .commandPool = m_frameData[i].cmdBuffer.m_cmdPool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount = 1,
        };
        VK_CHECK(vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, &m_frameData[i].cmdBuffer.m_cmdBuffer));
        DBG_VK_NAME(m_frameData[i].cmdBuffer.m_cmdBuffer);
    }
}

bool gfx::VulkanRenderer::BeginFrame()
{
    VulkanWindow* windowManager = static_cast<VulkanWindow*>(gfx::Window::instance.get());
    VkDevice device = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getDevice();

    // Get the frame data for the current frame in the ring buffer
    auto& frame = m_frameData[m_frameRingCurrent];

    // Check if swapchain needs rebuilding (this internally calls vkQueueWaitIdle())
    if (windowManager->swapChain.needRebuilding())
    {
        VkExtent2D size = windowManager->swapChain.reinitResources(windowManager->GetWindowVSync());
        windowManager->SetWindowSize((int)size.width, (int)size.height);
    }

    // Wait until GPU has finished processing the frame that was using these resources previously
    // Note: If swapchain was rebuilt above, this wait is essentially a no-op since vkQueueWaitIdle() was already called
    const VkSemaphoreWaitInfo waitInfo = {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
        .semaphoreCount = 1,
        .pSemaphores = &m_frameTimelineSemaphore,
        .pValues = &frame.frameNumber,
    };
    vkWaitSemaphores(device, &waitInfo, std::numeric_limits<uint64_t>::max());

    VkResult result = windowManager->swapChain.acquireNextImage();
    return (result == VK_SUCCESS || result == VK_SUBOPTIMAL_KHR);  // Continue only if we got a valid image
}

void gfx::VulkanRenderer::EndFrame()
{
    VulkanWindow* windowManager = static_cast<VulkanWindow*>(gfx::Window::instance.get());

    auto& frame = m_frameData[m_frameRingCurrent];
    
    /*--
     * Execute a stub pass if the renderpass was never invoced
    -*/
    if (frame.cmdBuffer.m_state != gfx::CommandBufferState::CAPTURED)
        gfx::CommandBuffer* cmdBuffer = BeginCommandRecording();
    
    /*--
     * Set the command buffer as empty because we are about to upload it
    -*/
    frame.cmdBuffer.m_state = gfx::CommandBufferState::EMPTY;

    VkCommandBuffer cmd = frame.cmdBuffer.m_cmdBuffer;
    // Ends recording of commands for the frame
    VK_CHECK(vkEndCommandBuffer(cmd));

    /*--
     * Prepare to submit the current frame for rendering
     * First add the swapchain semaphore to wait for the image to be available.
    -*/
    std::vector<VkSemaphoreSubmitInfo> waitSemaphores;
    std::vector<VkSemaphoreSubmitInfo> signalSemaphores;
    waitSemaphores.push_back({
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = windowManager->swapChain.getImageAvailableSemaphore(),
        .stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        });
    signalSemaphores.push_back({
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = windowManager->swapChain.getRenderFinishedSemaphore(),
        .stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        });

    /*--
     * Calculate the signal value for when this frame completes
     * Signal value = current frame number + numFramesInFlight
     * Example with 3 frames in flight:
     *   Frame 0 signals value 3 (allowing Frame 3 to start when complete)
     *   Frame 1 signals value 4 (allowing Frame 4 to start when complete)
    -*/
    const uint64_t signalFrameValue = frame.frameNumber + windowManager->swapChain.getMaxFramesInFlight();
    frame.frameNumber = signalFrameValue;  // Store for next time this frame buffer is used

    /*--
     * Add timeline semaphore to signal when GPU completes this frame
     * The color attachment output stage is used since that's when the frame is fully rendered
    -*/
    signalSemaphores.push_back({
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
        .semaphore = m_frameTimelineSemaphore,
        .value = signalFrameValue,
        .stageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        });

    // Note : in this sample, we only have one command buffer per frame.
    const std::array<VkCommandBufferSubmitInfo, 1> cmdBufferInfo{ {{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
        .commandBuffer = cmd,
    }} };

    // Populate the submit info to synchronize rendering and send the command buffer
    const std::array<VkSubmitInfo2, 1> submitInfo{ {{
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
        .waitSemaphoreInfoCount = uint32_t(waitSemaphores.size()),    //
        .pWaitSemaphoreInfos = waitSemaphores.data(),              // Wait for the image to be available
        .commandBufferInfoCount = uint32_t(cmdBufferInfo.size()),     //
        .pCommandBufferInfos = cmdBufferInfo.data(),               // Command buffer to submit
        .signalSemaphoreInfoCount = uint32_t(signalSemaphores.size()),  //
        .pSignalSemaphoreInfos = signalSemaphores.data(),            // Signal when rendering is finished
    }} };

    gfx::QueueInfo queue = static_cast<VulkanDevice*>(gfx::Device::instance.get())->getGraphicsQueue();

    // Submit the command buffer to the GPU and signal when it's done
    VK_CHECK(vkQueueSubmit2(queue.queue, uint32_t(submitInfo.size()), submitInfo.data(), nullptr));

    // Present the image
    windowManager->swapChain.presentFrame(queue.queue);

    // Move to the next frame
    m_frameRingCurrent = (m_frameRingCurrent + 1) % windowManager->swapChain.getMaxFramesInFlight();
}
