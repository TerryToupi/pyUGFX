/// \cond
#ifndef __VULKAN_RESOURCE_MANAGER_HPP__
#define __VULKAN_RESOURCE_MANAGER_HPP__

#include <pool.hpp>

#include <resources/resourceManger.hpp>

#include <resources/vulkanBindGroup.hpp>
#include <resources/vulkanBindGroupLayout.hpp>
#include <resources/vulkanBuffer.hpp>
#include <resources/vulkanDynamicBuffers.hpp>
#include <resources/vulkanDynamicBuffersLayout.hpp>
#include <resources/vulkanRenderPass.hpp>
#include <resources/vulkanRenderPassLayout.hpp>
#include <resources/vulkanSampler.hpp>
#include <resources/vulkanShader.hpp>
#include <resources/vulkanTexture.hpp>

namespace gfx
{
    class VulkanResourceManager : public ResourceManager
    {
    public:
        virtual void Init() override {};
        virtual void ShutDown() override {};

        virtual utils::Handle<Shader>               CreateShader(const gfx::ShaderDescriptor&& desc) override;
        virtual utils::Handle<BindGroup>            CreateBindGroup(const gfx::BindGroupDescriptor&& desc) override;
        virtual utils::Handle<BindGroupLayout>      CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc) override;
        virtual utils::Handle<Texture>              CreateTexture(const gfx::TextureDescriptor&& desc) override;
        virtual utils::Handle<Sampler>              CreateSampler(const gfx::SamplerDescriptor&& desc) override;
        virtual utils::Handle<Buffer>               CreateBuffer(const gfx::BufferDescriptor&& desc) override;
        virtual utils::Handle<DynamicBuffers>       CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc) override;
        virtual utils::Handle<DynamicBuffersLayout> CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc) override;
        virtual utils::Handle<RenderPass>           CreateRenderPass(const gfx::RenderPassDescriptor&& desc) override;
        virtual utils::Handle<RenderPassLayout>     CreateRenderPassLayout(const gfx::RenderPassLayoutDescriptor&& desc) override;

        virtual void Remove(utils::Handle<Shader> handle) override;
        virtual void Remove(utils::Handle<BindGroup> handle) override;
        virtual void Remove(utils::Handle<BindGroupLayout> handle) override;
        virtual void Remove(utils::Handle<Texture> handle) override;
        virtual void Remove(utils::Handle<Sampler> handle) override;
        virtual void Remove(utils::Handle<Buffer> handle) override;
        virtual void Remove(utils::Handle<DynamicBuffers> handle) override;
        virtual void Remove(utils::Handle<DynamicBuffersLayout> handle) override;
        virtual void Remove(utils::Handle<RenderPass> handle) override;
        virtual void Remove(utils::Handle<RenderPassLayout> handle) override;

        virtual void SetBufferData(utils::Handle<Buffer> buffer, uint32_t offset, const void* data, uint32_t size) override;
        virtual void SetBufferData(utils::Handle<DynamicBuffer> buffer, uint32_t offset, const void* data, uint32_t size) override;

        virtual void ResizeDynamicBuffer(utils::Handle<DynamicBuffer> buffer) override;

        utils::Handle<Shader>               Add(const VulkanShader& shader);
        utils::Handle<BindGroup>            Add(const VulkanBindGroup& bindGroup);
        utils::Handle<BindGroupLayout>      Add(const VulkanBindGroupLayout& bindGroupLayout);
        utils::Handle<Texture>              Add(const VulkanTexture& texture);
        utils::Handle<Sampler>              Add(const VulkanSampler& sampler);
        utils::Handle<Buffer>               Add(const VulkanBuffer& buffer);
        utils::Handle<DynamicBuffers>       Add(const VulkanDynamicBuffers& buffer);
        utils::Handle<DynamicBuffersLayout> Add(const VulkanDynamicBuffersLayout& buffer);
        utils::Handle<RenderPass>           Add(const VulkanRenderPass& renderPass);
        utils::Handle<RenderPassLayout>     Add(const VulkanRenderPassLayout& renderPassLayout);

        VulkanShader*                Get(utils::Handle<Shader> handle);
        VulkanBindGroup*             Get(utils::Handle<BindGroup> handle);
        VulkanBindGroupLayout*       Get(utils::Handle<BindGroupLayout> handle);
        VulkanTexture*               Get(utils::Handle<Texture> handle);
        VulkanSampler*               Get(utils::Handle<Sampler> handle);
        VulkanBuffer*                Get(utils::Handle<Buffer> handle);
        VulkanDynamicBuffers*        Get(utils::Handle<DynamicBuffers> handle);
        VulkanDynamicBuffersLayout*  Get(utils::Handle<DynamicBuffersLayout> handle);
        VulkanRenderPass*            Get(utils::Handle<RenderPass> handle);
        VulkanRenderPassLayout*      Get(utils::Handle<RenderPassLayout> handle);

    private:
        utils::Pool<VulkanShader, Shader> m_Shaders{ 32u, "Shaders" };
        utils::Pool<VulkanBindGroup, BindGroup> m_BindGroups{ 32u, "BindGroups" };
        utils::Pool<VulkanBindGroupLayout, BindGroupLayout> m_BindGroupLayouts{ 32u, "BindGroupLayouts" };
        utils::Pool<VulkanTexture, Texture> m_Textures{ 32u, "Textures" };
        utils::Pool<VulkanSampler, Sampler> m_Samplers{ 32u, "Samplers" };
        utils::Pool<VulkanBuffer, Buffer> m_Buffers{ 32u, "Buffers" };
        utils::Pool<VulkanDynamicBuffers, DynamicBuffers> m_DynamicBuffers{ 32u, "DynamicBuffers" };
        utils::Pool<VulkanDynamicBuffersLayout, DynamicBuffersLayout> m_DynamicBuffersLayout{ 32u, "DynamicBuffersLayout" };
        utils::Pool<VulkanRenderPass, RenderPass> m_RenderPasses{ 32u, "RenderPasses" };
        utils::Pool<VulkanRenderPassLayout, RenderPassLayout> m_RenderPassLayouts{ 32u, "RenderPassLayouts" };

    };
}

#endif // !__DAWN_RESOURCE_MANAGER_HPP__
/// \endcond
