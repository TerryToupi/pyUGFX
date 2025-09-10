/// \cond

#ifndef __VULKAN_ENUMS_HPP__
#define __VULKAN_ENUMS_HPP__

#include <enums.hpp>
#include <vulkanCommon.hpp>

namespace gfx
{
    VkShaderStageFlags DecodeShaderType(const gfx::ShaderStage& type);
    VkDescriptorType DecodeBufferBindingType(const gfx::BufferBindingType& type);
    VkCompareOp DecodeCompareType(const gfx::Compare& type);
    VkFormat DecodeVertexFormatType(const gfx::VertexFormat& type);
    VkFilter DecodeFilterModeType(const gfx::Filter& type);
    VkSamplerAddressMode DecodeWrapType(const gfx::Wrap& type);
    VkPrimitiveTopology DecodeTopologyType(const gfx::Topology& type);
    VkCullModeFlags DecodeCullModeType(const gfx::CullMode& type);
    VkFormat DecodeTextureFormatType(const gfx::TextureFormat& type);
    gfx::TextureFormat EncodeTextureFormatType(const VkFormat& type);
    VkImageViewType DecodeTextureSampleType(const gfx::TextureSampleType& type);
    VkBufferUsageFlags DecodeBufferUsageType(const gfx::BufferUsage& type);
    VkImageType DecodeTextureType(const gfx::TextureType& type);
    VkImageViewType DecodeTextureDimensionType(const gfx::TextureDimention& type);
    VkImageAspectFlags DecodeTextureAspectType(const gfx::TextureAspect& type);
    VkImageUsageFlags DecodeTextureUsageType(const gfx::TextureUsage& type);
    VkBlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type);
    VkBlendOp DecodeBlendOperationType(const gfx::BlendOperation& type);
    VkAttachmentStoreOp DecodeStoreOperationType(const gfx::StoreOperation& type);
    VkAttachmentLoadOp DecodeLoadOperationType(const gfx::LoadOperation& type);
    uint32_t DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type);
}

#endif // !__VULKAN_ENUMS_HPP__

/// \endcond
