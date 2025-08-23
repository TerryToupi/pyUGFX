/// \cond

#include <render/vulkanPassRenderer.hpp>

void gfx::VulkanCommandBuffer::BeginRenderPass(utils::Handle<RenderPass> renderPass, utils::Span<uint32_t> drawCalls)
{
}

void gfx::VulkanCommandBuffer::BeginComputePass(utils::Span<utils::Handle<Texture>> textureWrite, utils::Span<utils::Handle<Buffer>> bufferWrite, utils::Span<Dispatch> dispatches)
{
}

void gfx::VulkanCommandBuffer::Submit()
{
}

/// \endcond
