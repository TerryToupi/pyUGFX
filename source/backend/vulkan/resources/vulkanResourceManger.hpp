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
#include <resources/vulkanSampler.hpp>
#include <resources/vulkanShader.hpp>
#include <resources/vulkanTexture.hpp>

namespace gfx
{
    class VulkanResourceManager : public ResourceManager
    {
    public:
        virtual void Init() override;
        virtual void ShutDown() override;

        virtual utils::Handle<gfx::Shader>               CreateShader(const gfx::ShaderDescriptor&& desc) override;
        virtual utils::Handle<gfx::BindGroup>            CreateBindGroup(const gfx::BindGroupDescriptor&& desc) override;
        virtual utils::Handle<gfx::BindGroupLayout>      CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc) override;
        virtual utils::Handle<gfx::Texture>              CreateTexture(const gfx::TextureDescriptor&& desc) override;
        virtual utils::Handle<gfx::Sampler>              CreateSampler(const gfx::SamplerDescriptor&& desc) override;
        virtual utils::Handle<gfx::Buffer>               CreateBuffer(const gfx::BufferDescriptor&& desc) override;
        virtual utils::Handle<gfx::DynamicBuffers>       CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc) override;
        virtual utils::Handle<gfx::DynamicBuffersLayout> CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc) override;

        virtual void Remove(utils::Handle<gfx::Shader> handle) override;
        virtual void Remove(utils::Handle<gfx::BindGroup> handle) override;
        virtual void Remove(utils::Handle<gfx::BindGroupLayout> handle) override;
        virtual void Remove(utils::Handle<gfx::Texture> handle) override;
        virtual void Remove(utils::Handle<gfx::Sampler> handle) override;
        virtual void Remove(utils::Handle<gfx::Buffer> handle) override;
        virtual void Remove(utils::Handle<gfx::DynamicBuffers> handle) override;
        virtual void Remove(utils::Handle<gfx::DynamicBuffersLayout> handle) override;

        utils::Handle<gfx::Shader>               Add(const gfx::VulkanShader& shader);
        utils::Handle<gfx::BindGroup>            Add(const gfx::VulkanBindGroup& bindGroup);
        utils::Handle<gfx::BindGroupLayout>      Add(const gfx::VulkanBindGroupLayout& bindGroupLayout);
        utils::Handle<gfx::Texture>              Add(const gfx::VulkanTexture& texture);
        utils::Handle<gfx::Sampler>              Add(const gfx::VulkanSampler& sampler);
        utils::Handle<gfx::Buffer>               Add(const gfx::VulkanBuffer& buffer);
        utils::Handle<gfx::DynamicBuffers>       Add(const gfx::VulkanDynamicBuffers& buffer);
        utils::Handle<gfx::DynamicBuffersLayout> Add(const gfx::VulkanDynamicBuffersLayout& buffer);

        gfx::VulkanShader*                Get(utils::Handle<gfx::Shader> handle);
        gfx::VulkanBindGroup*             Get(utils::Handle<gfx::BindGroup> handle);
        gfx::VulkanBindGroupLayout*       Get(utils::Handle<gfx::BindGroupLayout> handle);
        gfx::VulkanTexture*               Get(utils::Handle<gfx::Texture> handle);
        gfx::VulkanSampler*               Get(utils::Handle<gfx::Sampler> handle);
        gfx::VulkanBuffer*                Get(utils::Handle<gfx::Buffer> handle);
        gfx::VulkanDynamicBuffers*        Get(utils::Handle<gfx::DynamicBuffers> handle);
        gfx::VulkanDynamicBuffersLayout*  Get(utils::Handle<gfx::DynamicBuffersLayout> handle);

    private:
        utils::Pool<gfx::VulkanShader, gfx::Shader> m_Shaders{ 16u, "Shaders" };
        utils::Pool<gfx::VulkanBindGroup, gfx::BindGroup> m_BindGroups{ 16u, "BindGroups" };
        utils::Pool<gfx::VulkanBindGroupLayout, gfx::BindGroupLayout> m_BindGroupLayouts{ 16u, "BindGroupLayouts" };
        utils::Pool<gfx::VulkanTexture, gfx::Texture> m_Textures{ 32u, "Textures" };
        utils::Pool<gfx::VulkanSampler, gfx::Sampler> m_Samplers{ 32u, "Samplers" };
        utils::Pool<gfx::VulkanBuffer, gfx::Buffer> m_Buffers{ 32u, "Buffers" };
        utils::Pool<gfx::VulkanDynamicBuffers, gfx::DynamicBuffers> m_DynamicBuffers{ 16u, "DynamicBuffers" };
        utils::Pool<gfx::VulkanDynamicBuffersLayout, gfx::DynamicBuffersLayout> m_DynamicBuffersLayout{ 16u, "DynamicBuffersLayout" };
    };
}

#endif // !__DAWN_RESOURCE_MANAGER_HPP__
/// \endcond
