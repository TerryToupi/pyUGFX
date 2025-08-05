#ifndef __RESOURCE_MANAGER_HPP__ 
#define __RESOURCE_MANAGER_HPP__ 

#include <resources/bindGroup.hpp>
#include <resources/bindGroupLayout.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffers.hpp>
#include <resources/dynamicBuffersLayout.hpp>
#include <resources/renderPass.hpp>
#include <resources/sampler.hpp>
#include <resources/shader.hpp>
#include <resources/texture.hpp>
#include <resources/renderPassLayout.hpp>

#include <handle.hpp>

namespace gfx
{
	class ResourceManager
	{
	public: 
		static inline ResourceManager* instance = nullptr;

		virtual ~ResourceManager() = default;

		virtual void Init() = 0;
		virtual void ShutDown() = 0;

		virtual utils::Handle<Shader>				CreateShader(const gfx::ShaderDescriptor&& desc) = 0;
		virtual utils::Handle<BindGroup>			CreateBindGroup(const gfx::BindGroupDescriptor&& desc) = 0;
		virtual utils::Handle<BindGroupLayout>		CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc) = 0;
		virtual utils::Handle<Texture>				CreateTexture(const gfx::TextureDescriptor&& desc) = 0;
		virtual utils::Handle<Sampler>				CreateSampler(const gfx::SamplerDescriptor&& desc) = 0;
		virtual utils::Handle<Buffer>				CreateBuffer(const gfx::BufferDescriptor&& desc) = 0;
		virtual utils::Handle<DynamicBuffers>		CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc) = 0;
		virtual utils::Handle<DynamicBuffersLayout>	CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc) = 0;
		virtual utils::Handle<RenderPass>			CreateRenderPass(const gfx::RenderPassDescriptor&& desc) = 0;
        virtual utils::Handle<RenderPassLayout> 	CreateRenderPassLayout(const gfx::RenderPassLayoutDescriptor&& desc) = 0;

		virtual void Remove(utils::Handle<Shader> handle) = 0;
		virtual void Remove(utils::Handle<BindGroup> handle) = 0;
		virtual void Remove(utils::Handle<BindGroupLayout> handle) = 0;
		virtual void Remove(utils::Handle<Texture> handle) = 0;
		virtual void Remove(utils::Handle<Sampler> handle) = 0;
		virtual void Remove(utils::Handle<Buffer> handle) = 0;
		virtual void Remove(utils::Handle<DynamicBuffers> handle) = 0;
		virtual void Remove(utils::Handle<DynamicBuffersLayout> handle) = 0;
		virtual void Remove(utils::Handle<RenderPass> handle) = 0;
        virtual void Remove(utils::Handle<RenderPassLayout> handle) = 0;

		virtual void SetBufferData(utils::Handle<Buffer> buffer, uint32_t offset, const void* data, uint32_t size) = 0;
	};
}

#endif
