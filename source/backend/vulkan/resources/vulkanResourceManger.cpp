/// \cond
#include <resources/vulkanResourceManger.hpp>

void gfx::VulkanResourceManager::Init()
{
	gfx::GPUAllocator::init();
}

void gfx::VulkanResourceManager::ShutDown()
{
	gfx::GPUAllocator::deinit();
}

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

void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Shader> handle)
{
	VulkanShader* shader = m_Shaders.Get(handle);
	if (!shader)
		return;

	shader->Remove();
	m_Shaders.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::BindGroup> handle)
{
	VulkanBindGroup* bindGroup = m_BindGroups.Get(handle);
	if (!bindGroup)
		return;

	bindGroup->Remove();
	m_BindGroups.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::BindGroupLayout> handle)
{
	VulkanBindGroupLayout* bindGroupLayout = m_BindGroupLayouts.Get(handle);
	if (!bindGroupLayout)
		return;

	bindGroupLayout->Remove();
	m_BindGroupLayouts.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Texture> handle)
{
	VulkanTexture* texture = m_Textures.Get(handle);
	if (!texture)
		return;

	texture->Remove();
	m_Textures.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Sampler> handle)
{
	VulkanSampler* sampler = m_Samplers.Get(handle);
	if (!sampler)
		return;

	sampler->Remove();
	m_Samplers.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::Buffer> handle)
{
	VulkanBuffer* buffer = m_Buffers.Get(handle);
	if (!buffer)
		return;

	buffer->Remove();
	m_Buffers.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::DynamicBuffers> handle)
{
	VulkanDynamicBuffers* dynamic = m_DynamicBuffers.Get(handle);
	if (!dynamic)
		return;

	dynamic->Remove();
	m_DynamicBuffers.Remove(handle);
}
void gfx::VulkanResourceManager::Remove(utils::Handle<gfx::DynamicBuffersLayout> handle)
{
	VulkanDynamicBuffersLayout* dynamic = m_DynamicBuffersLayout.Get(handle);
	if (!dynamic)
		return;

	dynamic->Remove();
	m_DynamicBuffersLayout.Remove(handle);
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
/// \endcond

