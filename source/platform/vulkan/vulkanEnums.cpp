#include <vulkanEnums.hpp>

namespace gfx
{
    VkShaderStageFlags DecodeShaderType(const gfx::ShaderStage& type)
    {
        struct FlagMap {
            gfx::ShaderStage gfxFlag;
            VkShaderStageFlags vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::ShaderStage::VERTEX, VK_SHADER_STAGE_VERTEX_BIT },
            { gfx::ShaderStage::FRAGMENT, VK_SHADER_STAGE_FRAGMENT_BIT },
            { gfx::ShaderStage::COMPUTE, VK_SHADER_STAGE_COMPUTE_BIT },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        VkShaderStageFlags returnFlag = VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;

        bool first = true;
        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                if (first)
                    returnFlag = flag.vkFlag;
                else
                    returnFlag |= flag.vkFlag;
                
                first = false;
            }
        }

        return returnFlag;
    }

    VkDescriptorType DecodeBufferBindingType(const gfx::BufferBindingType& type)
    {
        struct FlagMap {
            gfx::BufferBindingType gfxFlag;
            VkDescriptorType vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::BufferBindingType::UNIFORM, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER },
            { gfx::BufferBindingType::UNIFORM_DYNAMIC_OFFSET, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC },
            { gfx::BufferBindingType::STORAGE, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER },
            { gfx::BufferBindingType::READ_ONLY_STORAGE, VK_DESCRIPTOR_TYPE_MAX_ENUM },
            { gfx::BufferBindingType::READ_WRITE_STORAGE, VK_DESCRIPTOR_TYPE_MAX_ENUM },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }

    VkCompareOp DecodeCompareType(const gfx::Compare& type)
    {
        struct FlagMap {
            gfx::Compare gfxFlag;
            VkCompareOp vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::Compare::UNDEFINED, VK_COMPARE_OP_MAX_ENUM },
            { gfx::Compare::NEVER, VK_COMPARE_OP_NEVER },
            { gfx::Compare::LESS, VK_COMPARE_OP_LESS },
            { gfx::Compare::LESS_OR_EQUAL, VK_COMPARE_OP_LESS_OR_EQUAL },
            { gfx::Compare::GREATER, VK_COMPARE_OP_GREATER },
            { gfx::Compare::GREATER_OR_EQUAL, VK_COMPARE_OP_GREATER_OR_EQUAL },
            { gfx::Compare::EQUAL, VK_COMPARE_OP_EQUAL },
            { gfx::Compare::NOT_EQUAL, VK_COMPARE_OP_NOT_EQUAL },
            { gfx::Compare::ALAWAYS, VK_COMPARE_OP_ALWAYS },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_COMPARE_OP_MAX_ENUM;
    }

    VkFormat DecodeVertexFormatType(const gfx::VertexFormat& type)
    {
        struct FlagMap {
            gfx::VertexFormat gfxFlag;
            VkFormat vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::VertexFormat::F16,    VK_FORMAT_R16_SFLOAT },
            { gfx::VertexFormat::F16x2,  VK_FORMAT_R16G16_SFLOAT },
            { gfx::VertexFormat::F16x4,  VK_FORMAT_R16G16B16A16_SFLOAT },
            { gfx::VertexFormat::I16,    VK_FORMAT_R16_SINT },
            { gfx::VertexFormat::I16x2,  VK_FORMAT_R16G16_SINT },
            { gfx::VertexFormat::I16x4,  VK_FORMAT_R16G16B16A16_SINT },
            { gfx::VertexFormat::U16,    VK_FORMAT_R16_UINT },
            { gfx::VertexFormat::U16x2,  VK_FORMAT_R16G16_UINT },
            { gfx::VertexFormat::U16x4,  VK_FORMAT_R16G16B16A16_UINT },

            { gfx::VertexFormat::F32,    VK_FORMAT_R32_SFLOAT },
            { gfx::VertexFormat::F32x2,  VK_FORMAT_R32G32_SFLOAT },
            { gfx::VertexFormat::F32x3,  VK_FORMAT_R32G32B32_SFLOAT },
            { gfx::VertexFormat::F32x4,  VK_FORMAT_R32G32B32A32_SFLOAT },
            { gfx::VertexFormat::I32,    VK_FORMAT_R32_SINT },
            { gfx::VertexFormat::I32x2,  VK_FORMAT_R32G32_SINT },
            { gfx::VertexFormat::I32x3,  VK_FORMAT_R32G32B32_SINT },
            { gfx::VertexFormat::I32x4,  VK_FORMAT_R32G32B32A32_SINT },
            { gfx::VertexFormat::U32,    VK_FORMAT_R32_UINT },
            { gfx::VertexFormat::U32x2,  VK_FORMAT_R32G32_UINT },
            { gfx::VertexFormat::U32x3,  VK_FORMAT_R32G32B32_UINT },
            { gfx::VertexFormat::U32x4,  VK_FORMAT_R32G32B32A32_UINT },

            { gfx::VertexFormat::UNORM8,    VK_FORMAT_R8_UNORM },
            { gfx::VertexFormat::UNORM8x2,  VK_FORMAT_R8G8_UNORM },
            { gfx::VertexFormat::UNORM8x4,  VK_FORMAT_R8G8B8A8_UNORM },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_FORMAT_R32_SFLOAT;
    }

    VkFilter DecodeFilterModeType(const gfx::Filter& type)
    {
        struct FlagMap {
            gfx::Filter gfxFlag;
            VkFilter vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::Filter::NEAREST, VK_FILTER_NEAREST },
            { gfx::Filter::LINEAR, VK_FILTER_LINEAR },
            { gfx::Filter::CUBIC, VK_FILTER_CUBIC_EXT },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_FILTER_MAX_ENUM;
    }

    VkSamplerAddressMode DecodeWrapType(const gfx::Wrap& type)
    {
        struct FlagMap {
            gfx::Wrap gfxFlag;
            VkSamplerAddressMode vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::Wrap::REPEAT, VK_SAMPLER_ADDRESS_MODE_REPEAT },
            { gfx::Wrap::REPEAT_MIRRORED, VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT },
            { gfx::Wrap::CLAMP_TO_EDGE, VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE },
            { gfx::Wrap::CLAMP_TO_BORDER, VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER },
            { gfx::Wrap::MIRROR_CLAMP_TO_EDGE, VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_SAMPLER_ADDRESS_MODE_MAX_ENUM;
    }

    VkPrimitiveTopology DecodeTopologyType(const gfx::Topology& type)
    {
        struct FlagMap {
            gfx::Topology gfxFlag;
            VkPrimitiveTopology vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::Topology::POINT_LIST,        VK_PRIMITIVE_TOPOLOGY_POINT_LIST },
            { gfx::Topology::LINE_LIST,         VK_PRIMITIVE_TOPOLOGY_LINE_LIST },
            { gfx::Topology::LINE_STRIP,        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP },
            { gfx::Topology::TRIANGLE_LIST,     VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST },
            { gfx::Topology::TRIANGLE_STRIP,    VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP },
            { gfx::Topology::TRIANGLE_FAN,      VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN },
            { gfx::Topology::PATCH_LIST,        VK_PRIMITIVE_TOPOLOGY_PATCH_LIST },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
    }

    VkCullModeFlags DecodeCullModeType(const gfx::CullMode& type)
    {
        struct FlagMap {
            gfx::CullMode gfxFlag;
            VkCullModeFlags vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::CullMode::NONE, VK_CULL_MODE_NONE },
            { gfx::CullMode::FRONT_FACE, VK_CULL_MODE_FRONT_BIT },
            { gfx::CullMode::BACK_FACE, VK_CULL_MODE_BACK_BIT },
            { gfx::CullMode::FRONT_AND_BACK, VK_CULL_MODE_FRONT_AND_BACK },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_CULL_MODE_FLAG_BITS_MAX_ENUM;
    }

    VkFormat DecodeTextureFormatType(const gfx::TextureFormat& type)
    {
        struct FlagMap {
            gfx::TextureFormat gfxFlag;
            VkFormat vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureFormat::RGBA32_FLOAT, VK_FORMAT_R32G32B32A32_SFLOAT },
            { gfx::TextureFormat::D24_STENCIL_8, VK_FORMAT_D24_UNORM_S8_UINT },
            { gfx::TextureFormat::D32_FLOAT, VK_FORMAT_D32_SFLOAT },
            { gfx::TextureFormat::D32_FLOAT_STENCIL_8, VK_FORMAT_D32_SFLOAT_S8_UINT },
            { gfx::TextureFormat::D24_PLUS, VK_FORMAT_X8_D24_UNORM_PACK32 },
            { gfx::TextureFormat::D16_UNORM, VK_FORMAT_D16_UNORM },
            { gfx::TextureFormat::RGBA16_FLOAT, VK_FORMAT_R16G16B16A16_SFLOAT },
            { gfx::TextureFormat::RGBA8_UNORM, VK_FORMAT_R8G8B8A8_UNORM },
            { gfx::TextureFormat::RG16_FLOAT, VK_FORMAT_R16G16_SFLOAT },
            { gfx::TextureFormat::RG32_FLOAT, VK_FORMAT_R32G32_SFLOAT },
            { gfx::TextureFormat::R32_FLOAT, VK_FORMAT_R32_SFLOAT },
            { gfx::TextureFormat::R16_FLOAT, VK_FORMAT_R16_SFLOAT },
            { gfx::TextureFormat::RGBA8_UNORM_SRGB, VK_FORMAT_R8G8B8A8_SRGB },
            { gfx::TextureFormat::BGRA8_UNORM_SRGB, VK_FORMAT_B8G8R8A8_SRGB },
            { gfx::TextureFormat::RGBA8_LINEAR, VK_FORMAT_MAX_ENUM },
            { gfx::TextureFormat::BGRA8_UNORM, VK_FORMAT_B8G8R8_UNORM },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_FORMAT_MAX_ENUM;
    }

    gfx::TextureFormat EncodeTextureFormatType(const VkFormat& type)
    {
        struct FlagMap {
            VkFormat vkFlag;
            gfx::TextureFormat gfxFlag;
        };

        const FlagMap flagMapping[] =
        {
            { VK_FORMAT_R32G32B32A32_SFLOAT, gfx::TextureFormat::RGBA32_FLOAT },
            { VK_FORMAT_D24_UNORM_S8_UINT, gfx::TextureFormat::D24_STENCIL_8 },
            { VK_FORMAT_D32_SFLOAT, gfx::TextureFormat::D32_FLOAT },
            { VK_FORMAT_D32_SFLOAT_S8_UINT, gfx::TextureFormat::D32_FLOAT_STENCIL_8 },
            { VK_FORMAT_X8_D24_UNORM_PACK32, gfx::TextureFormat::D24_PLUS },
            { VK_FORMAT_D16_UNORM, gfx::TextureFormat::D16_UNORM },
            { VK_FORMAT_R16G16B16A16_SFLOAT, gfx::TextureFormat::RGBA16_FLOAT },
            { VK_FORMAT_R8G8B8A8_UNORM, gfx::TextureFormat::RGBA8_UNORM },
            { VK_FORMAT_R16G16_SFLOAT, gfx::TextureFormat::RG16_FLOAT },
            { VK_FORMAT_R32G32_SFLOAT, gfx::TextureFormat::RG32_FLOAT },
            { VK_FORMAT_R32_SFLOAT, gfx::TextureFormat::R32_FLOAT },
            { VK_FORMAT_R16_SFLOAT, gfx::TextureFormat::R16_FLOAT },
            { VK_FORMAT_R8G8B8A8_SRGB, gfx::TextureFormat::RGBA8_UNORM_SRGB },
            { VK_FORMAT_B8G8R8A8_SRGB, gfx::TextureFormat::BGRA8_UNORM_SRGB },
            { VK_FORMAT_MAX_ENUM, gfx::TextureFormat::RGBA8_LINEAR },
            { VK_FORMAT_B8G8R8_UNORM, gfx::TextureFormat::BGRA8_UNORM },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue == static_cast<unsigned int>(flag.vkFlag))
            {
                return flag.gfxFlag;
            }
        }

        return gfx::TextureFormat::UNDEFINED;
    }

    VkImageViewType DecodeTextureSampleType(const gfx::TextureSampleType& type)
    {
        struct FlagMap {
            VkImageViewType vkFlag;
            gfx::TextureSampleType gfxFlag;
        };

        const FlagMap flagMaping[] =
        {
            { VK_IMAGE_VIEW_TYPE_MAX_ENUM, gfx::TextureSampleType::FLOAT_NO_FILTER },
            { VK_IMAGE_VIEW_TYPE_MAX_ENUM, gfx::TextureSampleType::DEPTH },
            { VK_IMAGE_VIEW_TYPE_MAX_ENUM, gfx::TextureSampleType::FLOAT },
            { VK_IMAGE_VIEW_TYPE_MAX_ENUM, gfx::TextureSampleType::UINT },
            { VK_IMAGE_VIEW_TYPE_MAX_ENUM, gfx::TextureSampleType::SINT },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_IMAGE_VIEW_TYPE_MAX_ENUM;
    }

    VkBufferUsageFlags DecodeBufferUsageType(const gfx::BufferUsage& type)
    {
        struct FlagMap {
            gfx::BufferUsage gfxFlag;
            VkBufferUsageFlags vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::BufferUsage::MAP_READ, VK_BUFFER_USAGE_TRANSFER_SRC_BIT },
            { gfx::BufferUsage::MAP_WRITE, VK_BUFFER_USAGE_TRANSFER_DST_BIT },
            { gfx::BufferUsage::COPY_SRC, VK_BUFFER_USAGE_TRANSFER_SRC_BIT },
            { gfx::BufferUsage::COPY_DST, VK_BUFFER_USAGE_TRANSFER_DST_BIT },
            { gfx::BufferUsage::INDEX, VK_BUFFER_USAGE_INDEX_BUFFER_BIT },
            { gfx::BufferUsage::VERTEX, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT },
            { gfx::BufferUsage::UNIFORM, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT },
            { gfx::BufferUsage::STORAGE, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT },
            { gfx::BufferUsage::INDIRECT, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT },
            { gfx::BufferUsage::QUERY_RESOLVE, VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM},
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        VkBufferUsageFlags returnFlag = VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;

        bool first = true;
        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                if (first)
                    returnFlag = flag.vkFlag;
                else
                    returnFlag |= flag.vkFlag;

                first = false;
            }
        }

        return returnFlag;
    }

    VkImageType DecodeTextureType(const gfx::TextureType& type)
    {
        struct FlagMap {
            gfx::TextureType gfxFlag;
            VkImageType vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureType::D1, VK_IMAGE_TYPE_1D },
            { gfx::TextureType::D2, VK_IMAGE_TYPE_2D },
            { gfx::TextureType::D3, VK_IMAGE_TYPE_3D },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_IMAGE_TYPE_MAX_ENUM;
    }

    VkImageViewType DecodeTextureDimensionType(const gfx::TextureDimention& type)
    {
        struct FlagMap {
            gfx::TextureDimention gfxFlag;
            VkImageViewType vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureDimention::D1,            VK_IMAGE_VIEW_TYPE_1D },
            { gfx::TextureDimention::D2,            VK_IMAGE_VIEW_TYPE_2D },
            { gfx::TextureDimention::D2_ARRAY,      VK_IMAGE_VIEW_TYPE_2D_ARRAY },
            { gfx::TextureDimention::CUBE,          VK_IMAGE_VIEW_TYPE_CUBE },
            { gfx::TextureDimention::CUBE_ARRAY,    VK_IMAGE_VIEW_TYPE_CUBE_ARRAY },
            { gfx::TextureDimention::D3,            VK_IMAGE_VIEW_TYPE_3D },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_IMAGE_VIEW_TYPE_MAX_ENUM;
    }

    VkImageAspectFlags DecodeTextureAspectType(const gfx::TextureAspect& type)
    {
        struct FlagMap {
            gfx::TextureAspect gfxFlag;
            VkImageAspectFlags vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureAspect::NONE,        VK_IMAGE_ASPECT_NONE }, // No aspect
            { gfx::TextureAspect::ALL,         VK_IMAGE_ASPECT_COLOR_BIT | VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT },
            { gfx::TextureAspect::STENCIL_ONLY, VK_IMAGE_ASPECT_STENCIL_BIT },
            { gfx::TextureAspect::DEPTH_ONLY,   VK_IMAGE_ASPECT_DEPTH_BIT },
            { gfx::TextureAspect::PLANE_0_ONLY, VK_IMAGE_ASPECT_PLANE_0_BIT },
            { gfx::TextureAspect::PLANE_1_ONLY, VK_IMAGE_ASPECT_PLANE_1_BIT },
            { gfx::TextureAspect::PLANE_2_ONLY, VK_IMAGE_ASPECT_PLANE_2_BIT },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
    }

    VkImageUsageFlags DecodeTextureUsageType(const gfx::TextureUsage& type)
    {
        struct FlagMap {
            gfx::TextureUsage gfxFlag;
            VkImageUsageFlags vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureUsage::COPY_SRC,          VK_IMAGE_USAGE_TRANSFER_SRC_BIT },
            { gfx::TextureUsage::COPY_DST,          VK_IMAGE_USAGE_TRANSFER_DST_BIT },
            { gfx::TextureUsage::TEXTURE_BINDING,   VK_IMAGE_USAGE_SAMPLED_BIT },
            { gfx::TextureUsage::STORAGE_BINDING,   VK_IMAGE_USAGE_STORAGE_BIT },
            { gfx::TextureUsage::RENDER_ATTACHMENT, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT },
            { gfx::TextureUsage::TRANSIENT,         VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        VkImageUsageFlags returnFlag = VK_IMAGE_USAGE_FLAG_BITS_MAX_ENUM;

        bool first = true;
        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                if (first)
                    returnFlag = flag.vkFlag;
                else
                    returnFlag |= flag.vkFlag;

                first = false;
            }
        }

        return returnFlag;
    }

    VkBlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type)
    {
        struct FlagMap {
            gfx::BlendFactor gfxFlag;
            VkBlendFactor vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::BlendFactor::SRC_ALPHA,            VK_BLEND_FACTOR_SRC_ALPHA },
            { gfx::BlendFactor::ONE_MINUS_SRC_ALPHA,  VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA },
            { gfx::BlendFactor::ONE,                  VK_BLEND_FACTOR_ONE },
            { gfx::BlendFactor::ZERO,                 VK_BLEND_FACTOR_ZERO },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_BLEND_FACTOR_MAX_ENUM;
    }

    VkBlendOp DecodeBlendOperationType(const gfx::BlendOperation& type)
    {
        struct FlagMap {
            gfx::BlendOperation gfxFlag;
            VkBlendOp vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::BlendOperation::ADD, VK_BLEND_OP_ADD },
            { gfx::BlendOperation::SUB, VK_BLEND_OP_SUBTRACT },
            { gfx::BlendOperation::MIN, VK_BLEND_OP_MIN },
            { gfx::BlendOperation::MAX, VK_BLEND_OP_MAX },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_BLEND_OP_MAX_ENUM;
    }

    VkAttachmentStoreOp DecodeStoreOperationType(const gfx::StoreOperation& type)
    {
        struct FlagMap {
            gfx::StoreOperation gfxFlag;
            VkAttachmentStoreOp vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::StoreOperation::STORE,   VK_ATTACHMENT_STORE_OP_STORE },
            { gfx::StoreOperation::DISCARD, VK_ATTACHMENT_STORE_OP_DONT_CARE },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_ATTACHMENT_STORE_OP_MAX_ENUM;
    }

    VkAttachmentLoadOp DecodeLoadOperationType(const gfx::LoadOperation& type)
    {
        struct FlagMap {
            gfx::LoadOperation gfxFlag;
            VkAttachmentLoadOp vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::LoadOperation::CLEAR, VK_ATTACHMENT_LOAD_OP_CLEAR },
            { gfx::LoadOperation::LOAD,  VK_ATTACHMENT_LOAD_OP_LOAD },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return VK_ATTACHMENT_LOAD_OP_MAX_ENUM;
    }

    unsigned int DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type)
    {
        struct FlagMap {
            gfx::TextureFormat gfxFlag;
            unsigned int vkFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureFormat::RGBA32_FLOAT, 16 },
            { gfx::TextureFormat::D24_STENCIL_8, 4 },
            { gfx::TextureFormat::D32_FLOAT, 4 },
            { gfx::TextureFormat::D32_FLOAT_STENCIL_8, 5 },
            { gfx::TextureFormat::D24_PLUS, 3 },
            { gfx::TextureFormat::D16_UNORM, 2 },
            { gfx::TextureFormat::RGBA16_FLOAT, 8 },
            { gfx::TextureFormat::RGBA8_UNORM, 4 },
            { gfx::TextureFormat::RG16_FLOAT, 4 },
            { gfx::TextureFormat::RG32_FLOAT, 8 },
            { gfx::TextureFormat::R32_FLOAT, 4 },
            { gfx::TextureFormat::R16_FLOAT, 2 },
            { gfx::TextureFormat::RGBA8_UNORM_SRGB, 4 },
            { gfx::TextureFormat::BGRA8_UNORM_SRGB, 4 },
            { gfx::TextureFormat::RGBA8_LINEAR, 4 },
            { gfx::TextureFormat::BGRA8_UNORM, 4 },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.vkFlag;
            }
        }

        return 0;
    }
}
