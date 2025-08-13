#ifndef __METAL_ENUMS_HPP__
#define __METAL_ENUMS_HPP__

#include <enums.hpp>
#include <metalCommon.hpp>

namespace gfx
{
    MTL::RenderStages DecodeShaderType(const gfx::ShaderStage& type);
    MTL::ArgumentType DecodeBufferBindingType(const gfx::BufferBindingType& type);
    MTL::CompareFunction DecodeCompareType(const gfx::Compare& type);
    MTL::VertexFormat DecodeVertexFormatType(const gfx::VertexFormat& type);
    MTL::SamplerMinMagFilter DecodeFilterModeType(const gfx::Filter& type);
    MTL::SamplerAddressMode DecodeWrapType(const gfx::Wrap& type);
    MTL::PrimitiveType DecodeTopologyType(const gfx::Topology& type);
    MTL::CullMode DecodeCullModeType(const gfx::CullMode& type);
    MTL::PixelFormat DecodeTextureFormatType(const gfx::TextureFormat& type);
    gfx::TextureFormat EncodeTextureFormatType(const MTL::PixelFormat& type);
    MTL::PixelFormat DecodeTextureSampleType(const gfx::TextureSampleType& type);
    MTL::ResourceOptions DecodeBufferUsageType(const gfx::BufferUsage& type);
    MTL::TextureType DecodeTextureType(const gfx::TextureType& type);
    MTL::TextureType DecodeTextureDimensionType(const gfx::TextureDimention& type);
    MTL::PixelFormat DecodeTextureAspectType(const gfx::TextureAspect& type);
    MTL::TextureUsage DecodeTextureUsageType(const gfx::TextureUsage& type);
    MTL::BlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type);
    MTL::BlendOperation DecodeBlendOperationType(const gfx::BlendOperation& type);
    MTL::StoreAction DecodeStoreOperationType(const gfx::StoreOperation& type);
    MTL::LoadAction DecodeLoadOperationType(const gfx::LoadOperation& type);
    uint32_t DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type);
}

#endif // !__METAL_ENUMS_HPP__

