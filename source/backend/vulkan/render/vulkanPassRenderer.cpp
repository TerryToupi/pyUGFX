#include <render/vulkanPassRenderer.hpp>
#include <vulkanWindow.hpp>
#include <vulkanDevice.hpp>

static void beginDynamicRenderingToSawpChain(const gfx::RenderDescriptor& desc, VkCommandBuffer cmd) 
{
    gfx::VulkanWindow* windowManager = static_cast<gfx::VulkanWindow*>(gfx::Window::instance.get());
    gfx::VulkanDevice* DeviceManager = static_cast<gfx::VulkanDevice*>(gfx::Device::instance.get());

    // Image to render to
    const std::array<VkRenderingAttachmentInfoKHR, 1> colorAttachment{ {{
        .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO_KHR,
        .imageView = windowManager->swapChain.getImageView(),
        .imageLayout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR,
        .loadOp = gfx::DecodeLoadOperationType(desc.swapTarget.loadOp),   // Clear the image (see clearValue)
        .storeOp = gfx::DecodeStoreOperationType(desc.swapTarget.storeOp),  // Store the image (keep the image)
        .clearValue = {{{
            (float)desc.swapTarget.clearColor[0], 
            (float)desc.swapTarget.clearColor[1], 
            (float)desc.swapTarget.clearColor[2], 
            (float)desc.swapTarget.clearColor[3]
        }}},
    }} };

    VkExtent2D windowSize;
    windowManager->GetWindowSize(reinterpret_cast<int*>(&windowSize.width), reinterpret_cast<int*>(&windowSize.height));
    // Details of the dynamic rendering
    const VkRenderingInfoKHR renderingInfo{
        .sType = VK_STRUCTURE_TYPE_RENDERING_INFO_KHR,
        .renderArea = {{0, 0}, windowSize},
        .layerCount = 1,
        .colorAttachmentCount = uint32_t(colorAttachment.size()),
        .pColorAttachments = colorAttachment.data(),
    };

    // Transition the swapchain image to the color attachment layout, needed when using dynamic rendering
    DeviceManager->cmdTransitionImageLayout(
        cmd,
        windowManager->swapChain.getImage(),
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    vkCmdBeginRendering(cmd, &renderingInfo);
}

static void endDynamicRenderingToSwapchain(VkCommandBuffer cmd)
{
    gfx::VulkanWindow* windowManager = static_cast<gfx::VulkanWindow*>(gfx::Window::instance.get());
    gfx::VulkanDevice* DeviceManager = static_cast<gfx::VulkanDevice*>(gfx::Device::instance.get());

    vkCmdEndRendering(cmd);

    // Transition the swapchain image back to the present layout
    DeviceManager->cmdTransitionImageLayout(
        cmd,
        windowManager->swapChain.getImage(),
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
}

void gfx::VulkanCommandBuffer::BeginRenderPass(const RenderDescriptor&& desc, utils::Span<uint32_t> drawCalls)
{
    if (desc.swapTarget.enabled)
        beginDynamicRenderingToSawpChain(desc, m_cmdBuffer);
    else;
    
    // Record commands for the renderpass
    {

    }

    if (desc.swapTarget.enabled)
        endDynamicRenderingToSwapchain(m_cmdBuffer);
    else;
}

void gfx::VulkanCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, utils::Span<Dispatch> dispatches)
{
}
