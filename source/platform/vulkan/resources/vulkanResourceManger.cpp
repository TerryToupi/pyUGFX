/// \cond
#include <resources/vulkanResourceManger.hpp>

utils::Handle<gfx::Shader> gfx::VulkanResourceManager::CreateShader(const gfx::ShaderDescriptor&& desc)
{
	return m_Shaders.Insert(VulkanShader(std::forward<const gfx::ShaderDescriptor>(desc)));
}
utils::Handle<gfx::BindGroup> gfx::VulkanResourceManager::CreateBindGroup(const gfx::BindGroupDescriptor&& desc)
{
	return m_BindGroups.Insert(VulkanBindGroup(std::forward<const gfx::BindGroupDescriptor>(desc)));
}
utils::Handle<gfx::BindGroupLayout> gfx::VulkanResourceManager::CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc)
{
	return m_BindGroupLayouts.Insert(VulkanBindGroupLayout(std::forward<const gfx::BindGroupLayoutDescriptor>(desc)));
}
utils::Handle<gfx::Texture> gfx::VulkanResourceManager::CreateTexture(const gfx::TextureDescriptor&& desc)
{
	return m_Textures.Insert(VulkanTexture(std::forward<const gfx::TextureDescriptor>(desc)));
}
utils::Handle<gfx::Sampler> gfx::VulkanResourceManager::CreateSampler(const gfx::SamplerDescriptor&& desc)
{
	return m_Samplers.Insert(VulkanSampler(std::forward<const gfx::SamplerDescriptor>(desc)));
}
utils::Handle<gfx::Buffer> gfx::VulkanResourceManager::CreateBuffer(const gfx::BufferDescriptor&& desc)
{
	return m_Buffers.Insert(VulkanBuffer(std::forward<const gfx::BufferDescriptor>(desc)));
}
utils::Handle<gfx::DynamicBuffers> gfx::VulkanResourceManager::CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc)
{
	return m_DynamicBuffers.Insert(VulkanDynamicBuffers(std::forward<const gfx::DynamicBuffersDescriptor>(desc)));
}
utils::Handle<gfx::DynamicBuffersLayout> gfx::VulkanResourceManager::CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc)
{
	return m_DynamicBuffersLayout.Insert(VulkanDynamicBuffersLayout(std::forward<const gfx::DynamicBuffersLayoutDescriptor>(desc)));
}
utils::Handle<gfx::RenderPass> gfx::VulkanResourceManager::CreateRenderPass(const gfx::RenderPassDescriptor&& desc)
{
	return m_RenderPasses.Insert(VulkanRenderPass(std::forward<const gfx::RenderPassDescriptor>(desc)));
}
utils::Handle<gfx::RenderPassLayout> gfx::VulkanResourceManager::CreateRenderPassLayout(const gfx::RenderPassLayoutDescriptor&& desc)
{
	return m_RenderPassLayouts.Insert(VulkanRenderPassLayout(std::forward<const gfx::RenderPassLayoutDescriptor>(desc)));
}

void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Shader> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::BindGroup> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::BindGroupLayout> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Texture> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Sampler> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Buffer> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::DynamicBuffers> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::DynamicBuffersLayout> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::RenderPass> handle)
{
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::RenderPassLayout> handle)
{
}

void gfx::VulkanResourceManager::SetBufferData(utils::Handle<Buffer> buffer, uint32_t offset, const void* data, uint32_t size)
{
}

utils::Handle<gfx::Shader> gfx::VulkanResourceManager::Add(const gfx::VulkanShader& shader)
{
	return m_Shaders.Insert(shader);
}
utils::Handle<gfx::BindGroup> gfx::VulkanResourceManager::Add(const gfx::VulkanBindGroup& bindGroup)
{
	return m_BindGroups.Insert(bindGroup);
}
utils::Handle<gfx::BindGroupLayout> gfx::VulkanResourceManager::Add(const gfx::VulkanBindGroupLayout& bindGroupLayout)
{
	return m_BindGroupLayouts.Insert(bindGroupLayout);
}
utils::Handle<gfx::Texture> gfx::VulkanResourceManager::Add(const gfx::VulkanTexture& texture)
{
	return m_Textures.Insert(texture);
}
utils::Handle<gfx::Sampler> gfx::VulkanResourceManager::Add(const gfx::VulkanSampler& sampler)
{
	return m_Samplers.Insert(sampler);
}
utils::Handle<gfx::Buffer> gfx::VulkanResourceManager::Add(const gfx::VulkanBuffer& buffer)
{
	return m_Buffers.Insert(buffer);
}
utils::Handle<gfx::DynamicBuffers> gfx::VulkanResourceManager::Add(const gfx::VulkanDynamicBuffers& buffer)
{
	return m_DynamicBuffers.Insert(buffer);
}
utils::Handle<gfx::DynamicBuffersLayout> gfx::VulkanResourceManager::Add(const gfx::VulkanDynamicBuffersLayout& buffer)
{
	return m_DynamicBuffersLayout.Insert(buffer);
}
utils::Handle<gfx::RenderPass> gfx::VulkanResourceManager::Add(const gfx::VulkanRenderPass& renderPass)
{
	return m_RenderPasses.Insert(renderPass);
}
utils::Handle<gfx::RenderPassLayout> gfx::VulkanResourceManager::Add(const gfx::VulkanRenderPassLayout& renderPassLayout)
{
	return m_RenderPassLayouts.Insert(renderPassLayout);
}


gfx::VulkanShader* gfx::VulkanResourceManager::Get(utils::Handle<gfx::Shader> handle)
{
	return m_Shaders.Get(handle);
}
gfx::VulkanBindGroup* gfx::VulkanResourceManager::Get(utils::Handle<gfx::BindGroup> handle)
{
	return m_BindGroups.Get(handle);
}
gfx::VulkanBindGroupLayout* gfx::VulkanResourceManager::Get(utils::Handle<gfx::BindGroupLayout> handle)
{
	return m_BindGroupLayouts.Get(handle);
}
gfx::VulkanTexture* gfx::VulkanResourceManager::Get(utils::Handle<gfx::Texture> handle)
{
	return m_Textures.Get(handle);
}
gfx::VulkanSampler* gfx::VulkanResourceManager::Get(utils::Handle<gfx::Sampler> handle)
{
	return m_Samplers.Get(handle);
}
gfx::VulkanBuffer* gfx::VulkanResourceManager::Get(utils::Handle<gfx::Buffer> handle)
{
	return m_Buffers.Get(handle);
}
gfx::VulkanDynamicBuffers* gfx::VulkanResourceManager::Get(utils::Handle<gfx::DynamicBuffers> handle)
{
	return m_DynamicBuffers.Get(handle);
}
gfx::VulkanDynamicBuffersLayout* gfx::VulkanResourceManager::Get(utils::Handle<gfx::DynamicBuffersLayout> handle)
{
	return m_DynamicBuffersLayout.Get(handle);
}
gfx::VulkanRenderPass* gfx::VulkanResourceManager::Get(utils::Handle<gfx::RenderPass> handle)
{
	return m_RenderPasses.Get(handle);
}
gfx::VulkanRenderPassLayout* gfx::VulkanResourceManager::Get(utils::Handle<gfx::RenderPassLayout> handle)
{
	return m_RenderPassLayouts.Get(handle);
}
/// \endcond

