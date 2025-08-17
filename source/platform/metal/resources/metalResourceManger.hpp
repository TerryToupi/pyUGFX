/// \cond
#ifndef __METAL_RESOURCE_MANAGER_HPP__
#define __METAL_RESOURCE_MANAGER_HPP__

#include <pool.hpp>

#include <resources/resourceManger.hpp>

#include <resources/metalBindGroup.hpp>
#include <resources/metalBindGroupLayout.hpp>
#include <resources/metalBuffer.hpp>
#include <resources/metalDynamicBuffers.hpp>
#include <resources/metalDynamicBuffersLayout.hpp>
#include <resources/metalRenderPass.hpp>
#include <resources/metalRenderPassLayout.hpp>
#include <resources/metalSampler.hpp>
#include <resources/metalShader.hpp>
#include <resources/metalTexture.hpp>

namespace gfx
{
    class MetalResourceManager : public ResourceManager
    {
    public:
        virtual void Init() override {};
        virtual void ShutDown() override {};

        virtual utils::Handle<gfx::Shader>               CreateShader(const gfx::ShaderDescriptor&& desc) override;
        virtual utils::Handle<gfx::BindGroup>            CreateBindGroup(const gfx::BindGroupDescriptor&& desc) override;
        virtual utils::Handle<gfx::BindGroupLayout>      CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc) override;
        virtual utils::Handle<gfx::Texture>              CreateTexture(const gfx::TextureDescriptor&& desc) override;
        virtual utils::Handle<gfx::Sampler>              CreateSampler(const gfx::SamplerDescriptor&& desc) override;
        virtual utils::Handle<gfx::Buffer>               CreateBuffer(const gfx::BufferDescriptor&& desc) override;
        virtual utils::Handle<gfx::DynamicBuffers>       CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc) override;
        virtual utils::Handle<gfx::DynamicBuffersLayout> CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc) override;
        virtual utils::Handle<gfx::RenderPass>           CreateRenderPass(const gfx::RenderPassDescriptor&& desc) override;
        virtual utils::Handle<gfx::RenderPassLayout>     CreateRenderPassLayout(const gfx::RenderPassLayoutDescriptor&& desc) override;

        virtual void Remove(utils::Handle<gfx::Shader> handle) override;
        virtual void Remove(utils::Handle<gfx::BindGroup> handle) override;
        virtual void Remove(utils::Handle<gfx::BindGroupLayout> handle) override;
        virtual void Remove(utils::Handle<gfx::Texture> handle) override;
        virtual void Remove(utils::Handle<gfx::Sampler> handle) override;
        virtual void Remove(utils::Handle<gfx::Buffer> handle) override;
        virtual void Remove(utils::Handle<gfx::DynamicBuffers> handle) override;
        virtual void Remove(utils::Handle<gfx::DynamicBuffersLayout> handle) override;
        virtual void Remove(utils::Handle<gfx::RenderPass> handle) override;
        virtual void Remove(utils::Handle<gfx::RenderPassLayout> handle) override;

        virtual void SetBufferData(utils::Handle<Buffer> buffer, uint32_t offset, const void* data, uint32_t size) override;

        utils::Handle<gfx::Shader>               Add(const gfx::MetalShader& shader);
        utils::Handle<gfx::BindGroup>            Add(const gfx::MetalBindGroup& bindGroup);
        utils::Handle<gfx::BindGroupLayout>      Add(const gfx::MetalBindGroupLayout& bindGroupLayout);
        utils::Handle<gfx::Texture>              Add(const gfx::MetalTexture& texture);
        utils::Handle<gfx::Sampler>              Add(const gfx::MetalSampler& sampler);
        utils::Handle<gfx::Buffer>               Add(const gfx::MetalBuffer& buffer);
        utils::Handle<gfx::DynamicBuffers>       Add(const gfx::MetalDynamicBuffers& buffer);
        utils::Handle<gfx::DynamicBuffersLayout> Add(const gfx::MetalDynamicBuffersLayout& buffer);
        utils::Handle<gfx::RenderPass>           Add(const gfx::MetalRenderPass& renderPass);
        utils::Handle<gfx::RenderPassLayout>     Add(const gfx::MetalRenderPassLayout& renderPassLayout);

        gfx::MetalShader* Get(utils::Handle<gfx::Shader> handle);
        gfx::MetalBindGroup* Get(utils::Handle<gfx::BindGroup> handle);
        gfx::MetalBindGroupLayout* Get(utils::Handle<gfx::BindGroupLayout> handle);
        gfx::MetalTexture* Get(utils::Handle<gfx::Texture> handle);
        gfx::MetalSampler* Get(utils::Handle<gfx::Sampler> handle);
        gfx::MetalBuffer* Get(utils::Handle<gfx::Buffer> handle);
        gfx::MetalDynamicBuffers* Get(utils::Handle<gfx::DynamicBuffers> handle);
        gfx::MetalDynamicBuffersLayout* Get(utils::Handle<gfx::DynamicBuffersLayout> handle);
        gfx::MetalRenderPass* Get(utils::Handle<gfx::RenderPass> handle);
        gfx::MetalRenderPassLayout* Get(utils::Handle<gfx::RenderPassLayout> handle);

    private:
        utils::Pool<gfx::MetalShader, gfx::Shader> m_Shaders{ 32u, "Shaders" };
        utils::Pool<gfx::MetalBindGroup, gfx::BindGroup> m_BindGroups{ 32u, "BindGroups" };
        utils::Pool<gfx::MetalBindGroupLayout, gfx::BindGroupLayout> m_BindGroupLayouts{ 32u, "BindGroupLayouts" };
        utils::Pool<gfx::MetalTexture, gfx::Texture> m_Textures{ 32u, "Textures" };
        utils::Pool<gfx::MetalSampler, gfx::Sampler> m_Samplers{ 32u, "Samplers" };
        utils::Pool<gfx::MetalBuffer, gfx::Buffer> m_Buffers{ 32u, "Buffers" };
        utils::Pool<gfx::MetalDynamicBuffers, gfx::DynamicBuffers> m_DynamicBuffers{ 32u, "DynamicBuffers" };
        utils::Pool<gfx::MetalDynamicBuffersLayout, gfx::DynamicBuffersLayout> m_DynamicBuffersLayout{ 32u, "DynamicBuffersLayout" };
        utils::Pool<gfx::MetalRenderPass, gfx::RenderPass> m_RenderPasses{ 32u, "RenderPasses" };
        utils::Pool<gfx::MetalRenderPassLayout, gfx::RenderPassLayout> m_RenderPassLayouts{ 32u, "RenderPassLayouts" };

    };
}

#endif // !__DAWN_RESOURCE_MANAGER_HPP__
/// \endcond

