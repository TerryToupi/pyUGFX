/// \cond
#include <resources/metalResourceManger.hpp>

utils::Handle<gfx::Shader> gfx::MetalResourceManager::CreateShader(const gfx::ShaderDescriptor&& desc)
{
	return m_Shaders.Insert(MetalShader(std::forward<const gfx::ShaderDescriptor>(desc)));
}
utils::Handle<gfx::BindGroup> gfx::MetalResourceManager::CreateBindGroup(const gfx::BindGroupDescriptor&& desc)
{
	return m_BindGroups.Insert(MetalBindGroup(std::forward<const gfx::BindGroupDescriptor>(desc)));
}
utils::Handle<gfx::BindGroupLayout> gfx::MetalResourceManager::CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc)
{
	return m_BindGroupLayouts.Insert(MetalBindGroupLayout(std::forward<const gfx::BindGroupLayoutDescriptor>(desc)));
}
utils::Handle<gfx::Texture> gfx::MetalResourceManager::CreateTexture(const gfx::TextureDescriptor&& desc)
{
	return m_Textures.Insert(MetalTexture(std::forward<const gfx::TextureDescriptor>(desc)));
}
utils::Handle<gfx::Sampler> gfx::MetalResourceManager::CreateSampler(const gfx::SamplerDescriptor&& desc)
{
	return m_Samplers.Insert(MetalSampler(std::forward<const gfx::SamplerDescriptor>(desc)));
}
utils::Handle<gfx::Buffer> gfx::MetalResourceManager::CreateBuffer(const gfx::BufferDescriptor&& desc)
{
	return m_Buffers.Insert(MetalBuffer(std::forward<const gfx::BufferDescriptor>(desc)));
}
utils::Handle<gfx::DynamicBuffers> gfx::MetalResourceManager::CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc)
{
	return m_DynamicBuffers.Insert(MetalDynamicBuffers(std::forward<const gfx::DynamicBuffersDescriptor>(desc)));
}
utils::Handle<gfx::DynamicBuffersLayout> gfx::MetalResourceManager::CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc)
{
	return m_DynamicBuffersLayout.Insert(MetalDynamicBuffersLayout(std::forward<const gfx::DynamicBuffersLayoutDescriptor>(desc)));
}
utils::Handle<gfx::RenderPass> gfx::MetalResourceManager::CreateRenderPass(const gfx::RenderPassDescriptor&& desc)
{
	return m_RenderPasses.Insert(MetalRenderPass(std::forward<const gfx::RenderPassDescriptor>(desc)));
}
utils::Handle<gfx::RenderPassLayout> gfx::MetalResourceManager::CreateRenderPassLayout(const gfx::RenderPassLayoutDescriptor&& desc)
{
	return m_RenderPassLayouts.Insert(MetalRenderPassLayout(std::forward<const gfx::RenderPassLayoutDescriptor>(desc)));
}

void gfx::MetalResourceManager::Remove(utils::Handle<gfx::Shader> handle)
{
	MetalShader* shader = m_Shaders.Get(handle);
	if (!shader)
		return;

	shader->Remove();
	m_Shaders.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::BindGroup> handle)
{
	MetalBindGroup* bindGroup = m_BindGroups.Get(handle);
	if (!bindGroup)
		return;

	bindGroup->Remove();
	m_BindGroups.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::BindGroupLayout> handle)
{
	MetalBindGroupLayout* bindGroupLayout = m_BindGroupLayouts.Get(handle);
	if (!bindGroupLayout)
		return;

	bindGroupLayout->Remove();
	m_BindGroupLayouts.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::Texture> handle)
{
	MetalTexture* texture = m_Textures.Get(handle);
	if (!texture)
		return;

	texture->Remove();
	m_Textures.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::Sampler> handle)
{
	MetalSampler* sampler = m_Samplers.Get(handle);
	if (!sampler)
		return;

	sampler->Remove();
	m_Samplers.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::Buffer> handle)
{
	MetalBuffer* buffer = m_Buffers.Get(handle);
	if (!buffer)
		return;

	buffer->Remove();
	m_Buffers.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::DynamicBuffers> handle)
{
	MetalDynamicBuffers* dynamic = m_DynamicBuffers.Get(handle);
	if (!dynamic)
		return;

	dynamic->Remove();
	m_DynamicBuffers.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::DynamicBuffersLayout> handle)
{
	MetalDynamicBuffersLayout* dynamic = m_DynamicBuffersLayout.Get(handle);
	if (!dynamic)
		return;

	dynamic->Remove();
	m_DynamicBuffersLayout.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::RenderPass> handle)
{
	MetalRenderPass* renderPass = m_RenderPasses.Get(handle);
	if (!renderPass)
		return;

	renderPass->Remove();
	m_RenderPasses.Remove(handle);
}
void gfx::MetalResourceManager::Remove(utils::Handle<gfx::RenderPassLayout> handle)
{
	MetalRenderPassLayout* renderLayout = m_RenderPassLayouts.Get(handle);
	if (!renderLayout)
		return;

	renderLayout->Remove();
	m_RenderPassLayouts.Remove(handle);
}

void gfx::MetalResourceManager::SetBufferData(utils::Handle<Buffer> buffer, uint32_t offset, const void* data, uint32_t size)
{
}

utils::Handle<gfx::Shader> gfx::MetalResourceManager::Add(const gfx::MetalShader& shader)
{
	return m_Shaders.Insert(shader);
}
utils::Handle<gfx::BindGroup> gfx::MetalResourceManager::Add(const gfx::MetalBindGroup& bindGroup)
{
	return m_BindGroups.Insert(bindGroup);
}
utils::Handle<gfx::BindGroupLayout> gfx::MetalResourceManager::Add(const gfx::MetalBindGroupLayout& bindGroupLayout)
{
	return m_BindGroupLayouts.Insert(bindGroupLayout);
}
utils::Handle<gfx::Texture> gfx::MetalResourceManager::Add(const gfx::MetalTexture& texture)
{
	return m_Textures.Insert(texture);
}
utils::Handle<gfx::Sampler> gfx::MetalResourceManager::Add(const gfx::MetalSampler& sampler)
{
	return m_Samplers.Insert(sampler);
}
utils::Handle<gfx::Buffer> gfx::MetalResourceManager::Add(const gfx::MetalBuffer& buffer)
{
	return m_Buffers.Insert(buffer);
}
utils::Handle<gfx::DynamicBuffers> gfx::MetalResourceManager::Add(const gfx::MetalDynamicBuffers& buffer)
{
	return m_DynamicBuffers.Insert(buffer);
}
utils::Handle<gfx::DynamicBuffersLayout> gfx::MetalResourceManager::Add(const gfx::MetalDynamicBuffersLayout& buffer)
{
	return m_DynamicBuffersLayout.Insert(buffer);
}
utils::Handle<gfx::RenderPass> gfx::MetalResourceManager::Add(const gfx::MetalRenderPass& renderPass)
{
	return m_RenderPasses.Insert(renderPass);
}
utils::Handle<gfx::RenderPassLayout> gfx::MetalResourceManager::Add(const gfx::MetalRenderPassLayout& renderPassLayout)
{
	return m_RenderPassLayouts.Insert(renderPassLayout);
}


gfx::MetalShader* gfx::MetalResourceManager::Get(utils::Handle<gfx::Shader> handle)
{
	return m_Shaders.Get(handle);
}
gfx::MetalBindGroup* gfx::MetalResourceManager::Get(utils::Handle<gfx::BindGroup> handle)
{
	return m_BindGroups.Get(handle);
}
gfx::MetalBindGroupLayout* gfx::MetalResourceManager::Get(utils::Handle<gfx::BindGroupLayout> handle)
{
	return m_BindGroupLayouts.Get(handle);
}
gfx::MetalTexture* gfx::MetalResourceManager::Get(utils::Handle<gfx::Texture> handle)
{
	return m_Textures.Get(handle);
}
gfx::MetalSampler* gfx::MetalResourceManager::Get(utils::Handle<gfx::Sampler> handle)
{
	return m_Samplers.Get(handle);
}
gfx::MetalBuffer* gfx::MetalResourceManager::Get(utils::Handle<gfx::Buffer> handle)
{
	return m_Buffers.Get(handle);
}
gfx::MetalDynamicBuffers* gfx::MetalResourceManager::Get(utils::Handle<gfx::DynamicBuffers> handle)
{
	return m_DynamicBuffers.Get(handle);
}
gfx::MetalDynamicBuffersLayout* gfx::MetalResourceManager::Get(utils::Handle<gfx::DynamicBuffersLayout> handle)
{
	return m_DynamicBuffersLayout.Get(handle);
}
gfx::MetalRenderPass* gfx::MetalResourceManager::Get(utils::Handle<gfx::RenderPass> handle)
{
	return m_RenderPasses.Get(handle);
}
gfx::MetalRenderPassLayout* gfx::MetalResourceManager::Get(utils::Handle<gfx::RenderPassLayout> handle)
{
	return m_RenderPassLayouts.Get(handle);
}
/// \endcond

