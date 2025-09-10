/**
 * @file resourceManager.hpp
 * @brief Interface for managing GPU resources such as shaders, textures, buffers, and render passes.
 *
 * Provides creation, removal, and management of GPU resources via handles.
 * Acts as a central manager for all resource lifetimes.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include <common.hpp>

#include <resources/bindGroup.hpp>
#include <resources/bindGroupLayout.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffers.hpp>
#include <resources/dynamicBuffersLayout.hpp>
#include <resources/sampler.hpp>
#include <resources/shader.hpp>
#include <resources/texture.hpp>

#include <handle.hpp>

namespace gfx
{
    /**
     * @brief Central interface for managing GPU resources.
     *
     * Responsible for creation, removal, and updating of GPU resources such as
     * shaders, textures, buffers, samplers, render passes, and bind groups.
     */
    class ResourceManager
    {
    public:
        /// Singleton instance pointer
        static inline sPtr<ResourceManager> instance = nullptr;

        virtual ~ResourceManager() = default;

        /// Initialize the resource manager.
        virtual void Init() = 0;

        /// Shut down the resource manager and free all resources.
        virtual void ShutDown() = 0;

        /**
         * @brief Create a new shader resource.
         * @param desc Shader descriptor.
         * @return Handle to the created shader.
         */
        virtual utils::Handle<Shader> CreateShader(const gfx::ShaderDescriptor&& desc) = 0;
        virtual utils::Handle<BindGroup> CreateBindGroup(const gfx::BindGroupDescriptor&& desc) = 0;
        virtual utils::Handle<BindGroupLayout> CreateBindGroupLayout(const gfx::BindGroupLayoutDescriptor&& desc) = 0;
        virtual utils::Handle<Texture> CreateTexture(const gfx::TextureDescriptor&& desc) = 0;
        virtual utils::Handle<Sampler> CreateSampler(const gfx::SamplerDescriptor&& desc) = 0;
        virtual utils::Handle<Buffer> CreateBuffer(const gfx::BufferDescriptor&& desc) = 0;
        virtual utils::Handle<DynamicBuffers> CreateDynamicBuffers(const gfx::DynamicBuffersDescriptor&& desc) = 0;
        virtual utils::Handle<DynamicBuffersLayout> CreateDynamicBuffersLayout(const gfx::DynamicBuffersLayoutDescriptor&& desc) = 0;

        /**
         * @brief Remove a GPU resource.
         * @param handle Handle to the resource to remove.
         */
        virtual void Remove(utils::Handle<Shader> handle) = 0;
        virtual void Remove(utils::Handle<BindGroup> handle) = 0;
        virtual void Remove(utils::Handle<BindGroupLayout> handle) = 0;
        virtual void Remove(utils::Handle<Texture> handle) = 0;
        virtual void Remove(utils::Handle<Sampler> handle) = 0;
        virtual void Remove(utils::Handle<Buffer> handle) = 0;
        virtual void Remove(utils::Handle<DynamicBuffers> handle) = 0;
        virtual void Remove(utils::Handle<DynamicBuffersLayout> handle) = 0;
    };
}

#endif // !__RESOURCE_MANAGER_HPP__
