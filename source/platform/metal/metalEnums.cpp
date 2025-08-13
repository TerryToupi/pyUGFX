#include <metalEnums.hpp>

namespace gfx
{
    MTL::RenderStages DecodeShaderType(const gfx::ShaderStage& type)
    {
        struct FlagMap {
            gfx::ShaderStage gfxFlag;
            MTL::RenderStages mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::ShaderStage::VERTEX,   MTL::RenderStageVertex   },
            { gfx::ShaderStage::FRAGMENT, MTL::RenderStageFragment },
            { gfx::ShaderStage::COMPUTE,  (MTL::RenderStages)0 } // No compute in RenderStages
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        MTL::RenderStages returnFlag = (MTL::RenderStages)0;

        bool first = true;
        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                if (first)
                    returnFlag = flag.mtlFlag;
                else
                    returnFlag = (MTL::RenderStages)(returnFlag | flag.mtlFlag);

                first = false;
            }
        }

        return returnFlag;
    }

    MTL::ArgumentType DecodeBufferBindingType(const gfx::BufferBindingType& type)
    {
        struct FlagMap {
            gfx::BufferBindingType gfxFlag;
            MTL::ArgumentType mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::BufferBindingType::UNIFORM,               MTL::ArgumentTypeBuffer },
            { gfx::BufferBindingType::UNIFORM_DYNAMIC_OFFSET, MTL::ArgumentTypeBuffer }, // no direct Metal concept
            { gfx::BufferBindingType::STORAGE,               MTL::ArgumentTypeBuffer },
            { gfx::BufferBindingType::READ_ONLY_STORAGE,     MTL::ArgumentTypeBuffer }, // access controlled elsewhere
            { gfx::BufferBindingType::READ_WRITE_STORAGE,    MTL::ArgumentTypeBuffer },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::ArgumentTypeThreadgroupMemory; // default/fallback
    }

    MTL::CompareFunction DecodeCompareType(const gfx::Compare& type)
    {
        struct FlagMap {
            gfx::Compare gfxFlag;
            MTL::CompareFunction mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::Compare::UNDEFINED,         MTL::CompareFunctionNever }, // no "undefined" in Metal
            { gfx::Compare::NEVER,             MTL::CompareFunctionNever },
            { gfx::Compare::LESS,              MTL::CompareFunctionLess },
            { gfx::Compare::LESS_OR_EQUAL,     MTL::CompareFunctionLessEqual },
            { gfx::Compare::GREATER,           MTL::CompareFunctionGreater },
            { gfx::Compare::GREATER_OR_EQUAL,  MTL::CompareFunctionGreaterEqual },
            { gfx::Compare::EQUAL,             MTL::CompareFunctionEqual },
            { gfx::Compare::NOT_EQUAL,         MTL::CompareFunctionNotEqual },
            { gfx::Compare::ALAWAYS,           MTL::CompareFunctionAlways },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::CompareFunctionNever;
    }

    MTL::VertexFormat DecodeVertexFormatType(const gfx::VertexFormat& type)
    {
        struct FlagMap {
            gfx::VertexFormat gfxFlag;
            MTL::VertexFormat mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::VertexFormat::F16,    MTL::VertexFormatHalf },
            { gfx::VertexFormat::F16x2,  MTL::VertexFormatHalf2 },
            { gfx::VertexFormat::F16x4,  MTL::VertexFormatHalf4 },
            { gfx::VertexFormat::I16,    MTL::VertexFormatShort },
            { gfx::VertexFormat::I16x2,  MTL::VertexFormatShort2 },
            { gfx::VertexFormat::I16x4,  MTL::VertexFormatShort4 },
            { gfx::VertexFormat::U16,    MTL::VertexFormatUShort },
            { gfx::VertexFormat::U16x2,  MTL::VertexFormatUShort2 },
            { gfx::VertexFormat::U16x4,  MTL::VertexFormatUShort4 },

            { gfx::VertexFormat::F32,    MTL::VertexFormatFloat },
            { gfx::VertexFormat::F32x2,  MTL::VertexFormatFloat2 },
            { gfx::VertexFormat::F32x3,  MTL::VertexFormatFloat3 },
            { gfx::VertexFormat::F32x4,  MTL::VertexFormatFloat4 },
            { gfx::VertexFormat::I32,    MTL::VertexFormatInt },
            { gfx::VertexFormat::I32x2,  MTL::VertexFormatInt2 },
            { gfx::VertexFormat::I32x3,  MTL::VertexFormatInt3 },
            { gfx::VertexFormat::I32x4,  MTL::VertexFormatInt4 },
            { gfx::VertexFormat::U32,    MTL::VertexFormatUInt },
            { gfx::VertexFormat::U32x2,  MTL::VertexFormatUInt2 },
            { gfx::VertexFormat::U32x3,  MTL::VertexFormatUInt3 },
            { gfx::VertexFormat::U32x4,  MTL::VertexFormatUInt4 },

            { gfx::VertexFormat::UNORM8,   MTL::VertexFormatUCharNormalized },
            { gfx::VertexFormat::UNORM8x2, MTL::VertexFormatUChar2Normalized },
            { gfx::VertexFormat::UNORM8x4, MTL::VertexFormatUChar4Normalized },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::VertexFormatFloat; // default
    }

    MTL::SamplerMinMagFilter DecodeFilterModeType(const gfx::Filter& type)
    {
        struct FlagMap {
            gfx::Filter gfxFlag;
            MTL::SamplerMinMagFilter mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::Filter::NEAREST, MTL::SamplerMinMagFilterNearest },
            { gfx::Filter::LINEAR,  MTL::SamplerMinMagFilterLinear },
            // Metal has no cubic filter; you'd emulate with mip filtering or shader sampling
            { gfx::Filter::CUBIC,   MTL::SamplerMinMagFilterLinear },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::SamplerMinMagFilterNearest;
    }

    MTL::SamplerAddressMode DecodeWrapType(const gfx::Wrap& type)
    {
        struct FlagMap {
            gfx::Wrap gfxFlag;
            MTL::SamplerAddressMode mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::Wrap::REPEAT,               MTL::SamplerAddressModeRepeat },
            { gfx::Wrap::REPEAT_MIRRORED,      MTL::SamplerAddressModeMirrorRepeat },
            { gfx::Wrap::CLAMP_TO_EDGE,        MTL::SamplerAddressModeClampToEdge },
            { gfx::Wrap::CLAMP_TO_BORDER,      MTL::SamplerAddressModeClampToBorderColor },
            { gfx::Wrap::MIRROR_CLAMP_TO_EDGE, MTL::SamplerAddressModeMirrorClampToEdge },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::SamplerAddressModeClampToEdge;
    }

    MTL::PrimitiveType DecodeTopologyType(const gfx::Topology& type)
    {
        struct FlagMap {
            gfx::Topology gfxFlag;
            MTL::PrimitiveType mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::Topology::POINT_LIST,      MTL::PrimitiveTypePoint },
            { gfx::Topology::LINE_LIST,       MTL::PrimitiveTypeLine },
            { gfx::Topology::LINE_STRIP,      MTL::PrimitiveTypeLineStrip },
            { gfx::Topology::TRIANGLE_LIST,   MTL::PrimitiveTypeTriangle },
            { gfx::Topology::TRIANGLE_STRIP,  MTL::PrimitiveTypeTriangleStrip },
            { gfx::Topology::TRIANGLE_FAN,    MTL::PrimitiveTypeTriangle }, // Metal has no fan type; must convert in CPU
            { gfx::Topology::PATCH_LIST,      MTL::PrimitiveTypeTriangle
                
            },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::PrimitiveTypeTriangle;
    }

    MTL::CullMode DecodeCullModeType(const gfx::CullMode& type)
    {
        struct FlagMap {
            gfx::CullMode gfxFlag;
            MTL::CullMode mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::CullMode::NONE,           MTL::CullModeNone },
            { gfx::CullMode::FRONT_FACE,     MTL::CullModeFront },
            { gfx::CullMode::BACK_FACE,      MTL::CullModeBack },
            { gfx::CullMode::FRONT_AND_BACK, MTL::CullModeNone }, // Not supported in Metal
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
                return flag.mtlFlag;
        }

        return MTL::CullModeNone;
    }

    MTL::PixelFormat DecodeTextureFormatType(const gfx::TextureFormat& type)
    {
        struct FlagMap {
            gfx::TextureFormat gfxFlag;
            MTL::PixelFormat mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::TextureFormat::RGBA32_FLOAT,        MTL::PixelFormatRGBA32Float },
            { gfx::TextureFormat::D24_STENCIL_8,       MTL::PixelFormatDepth24Unorm_Stencil8 },
            { gfx::TextureFormat::D32_FLOAT,           MTL::PixelFormatDepth32Float },
            { gfx::TextureFormat::D32_FLOAT_STENCIL_8, MTL::PixelFormatDepth32Float_Stencil8 },
            { gfx::TextureFormat::D24_PLUS,            MTL::PixelFormatX24_Stencil8 },
            { gfx::TextureFormat::D16_UNORM,           MTL::PixelFormatDepth16Unorm },
            { gfx::TextureFormat::RGBA16_FLOAT,        MTL::PixelFormatRGBA16Float },
            { gfx::TextureFormat::RGBA8_UNORM,         MTL::PixelFormatRGBA8Unorm },
            { gfx::TextureFormat::RG16_FLOAT,          MTL::PixelFormatRG16Float },
            { gfx::TextureFormat::RG32_FLOAT,          MTL::PixelFormatRG32Float },
            { gfx::TextureFormat::R32_FLOAT,           MTL::PixelFormatR32Float },
            { gfx::TextureFormat::R16_FLOAT,           MTL::PixelFormatR16Float },
            { gfx::TextureFormat::RGBA8_UNORM_SRGB,    MTL::PixelFormatRGBA8Unorm_sRGB },
            { gfx::TextureFormat::BGRA8_UNORM_SRGB,    MTL::PixelFormatBGRA8Unorm_sRGB },
            { gfx::TextureFormat::RGBA8_LINEAR,        MTL::PixelFormatRGBA8Unorm },
            { gfx::TextureFormat::BGRA8_UNORM,         MTL::PixelFormatBGRA8Unorm },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
                return flag.mtlFlag;
        }

        return MTL::PixelFormatInvalid;
    }

    gfx::TextureFormat EncodeTextureFormatType(const MTL::PixelFormat& type)
    {
        struct FlagMap {
            MTL::PixelFormat mtlFlag;
            gfx::TextureFormat gfxFlag;
        };

        const FlagMap flagMapping[] =
        {
            { MTL::PixelFormatRGBA32Float,           gfx::TextureFormat::RGBA32_FLOAT },
            { MTL::PixelFormatDepth24Unorm_Stencil8, gfx::TextureFormat::D24_STENCIL_8 },
            { MTL::PixelFormatDepth32Float,          gfx::TextureFormat::D32_FLOAT },
            { MTL::PixelFormatDepth32Float_Stencil8, gfx::TextureFormat::D32_FLOAT_STENCIL_8 },
            { MTL::PixelFormatX24_Stencil8,          gfx::TextureFormat::D24_PLUS },
            { MTL::PixelFormatDepth16Unorm,          gfx::TextureFormat::D16_UNORM },
            { MTL::PixelFormatRGBA16Float,           gfx::TextureFormat::RGBA16_FLOAT },
            { MTL::PixelFormatRGBA8Unorm,            gfx::TextureFormat::RGBA8_UNORM },
            { MTL::PixelFormatRG16Float,             gfx::TextureFormat::RG16_FLOAT },
            { MTL::PixelFormatRG32Float,             gfx::TextureFormat::RG32_FLOAT },
            { MTL::PixelFormatR32Float,              gfx::TextureFormat::R32_FLOAT },
            { MTL::PixelFormatR16Float,              gfx::TextureFormat::R16_FLOAT },
            { MTL::PixelFormatRGBA8Unorm_sRGB,       gfx::TextureFormat::RGBA8_UNORM_SRGB },
            { MTL::PixelFormatBGRA8Unorm_sRGB,       gfx::TextureFormat::BGRA8_UNORM_SRGB },
            { MTL::PixelFormatRGBA8Unorm,            gfx::TextureFormat::RGBA8_LINEAR },
            { MTL::PixelFormatBGRA8Unorm,            gfx::TextureFormat::BGRA8_UNORM },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue == static_cast<unsigned int>(flag.mtlFlag))
                return flag.gfxFlag;
        }

        return gfx::TextureFormat::UNDEFINED;
    }

    MTL::PixelFormat DecodeTextureSampleType(const gfx::TextureSampleType& type)
    {
        struct FlagMap {
            gfx::TextureSampleType gfxFlag;
            MTL::PixelFormat mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::TextureSampleType::FLOAT_NO_FILTER, MTL::PixelFormatRGBA8Unorm },
            { gfx::TextureSampleType::DEPTH,           MTL::PixelFormatDepth32Float },
            { gfx::TextureSampleType::FLOAT,           MTL::PixelFormatRGBA16Float },
            { gfx::TextureSampleType::UINT,            MTL::PixelFormatRGBA8Uint },
            { gfx::TextureSampleType::SINT,            MTL::PixelFormatRGBA8Sint },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
                return flag.mtlFlag;
        }

        return MTL::PixelFormatInvalid;
    }

    MTL::ResourceOptions DecodeBufferUsageType(const gfx::BufferUsage& type)
    {
        struct FlagMap {
            gfx::BufferUsage gfxFlag;
            MTL::ResourceOptions mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::BufferUsage::MAP_READ,     MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::MAP_WRITE,    MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::COPY_SRC,     MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::COPY_DST,     MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::INDEX,        MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::VERTEX,       MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::UNIFORM,      MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::STORAGE,      MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::INDIRECT,     MTL::ResourceStorageModeShared },
            { gfx::BufferUsage::QUERY_RESOLVE,MTL::ResourceStorageModeShared },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        MTL::ResourceOptions returnFlag = MTL::ResourceStorageModeShared;
        bool first = true;

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                if (first)
                    returnFlag = flag.mtlFlag;
                else
                    returnFlag = static_cast<MTL::ResourceOptions>(returnFlag | flag.mtlFlag);

                first = false;
            }
        }

        return returnFlag;
    }

    MTL::TextureType DecodeTextureType(const gfx::TextureType& type)
    {
        struct FlagMap {
            gfx::TextureType gfxFlag;
            MTL::TextureType mtlFlag;
        };

        const FlagMap flagMapping[] =
        {
            { gfx::TextureType::D1, MTL::TextureType1D },
            { gfx::TextureType::D2, MTL::TextureType2D },
            { gfx::TextureType::D3, MTL::TextureType3D },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMapping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
                return flag.mtlFlag;
        }

        return MTL::TextureType1D; // default
    }

    MTL::TextureType DecodeTextureDimensionType(const gfx::TextureDimention& type)
    {
        struct FlagMap {
            gfx::TextureDimention gfxFlag;
            MTL::TextureType mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureDimention::D1,            MTL::TextureType1D },
            { gfx::TextureDimention::D2,            MTL::TextureType2D },
            { gfx::TextureDimention::D2_ARRAY,      MTL::TextureType2DArray },
            { gfx::TextureDimention::CUBE,          MTL::TextureTypeCube },
            { gfx::TextureDimention::CUBE_ARRAY,    MTL::TextureTypeCubeArray },
            { gfx::TextureDimention::D3,            MTL::TextureType3D },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::TextureType2D; // default fallback
    }

    MTL::PixelFormat DecodeTextureAspectType(const gfx::TextureAspect& type)
    {
        struct FlagMap {
            gfx::TextureAspect gfxFlag;
            MTL::PixelFormat mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureAspect::NONE,         MTL::PixelFormatInvalid },
            { gfx::TextureAspect::ALL,          MTL::PixelFormatInvalid }, // ALL isn't directly a Metal format
            { gfx::TextureAspect::STENCIL_ONLY, MTL::PixelFormatStencil8 },
            { gfx::TextureAspect::DEPTH_ONLY,   MTL::PixelFormatDepth32Float },
            { gfx::TextureAspect::PLANE_0_ONLY, MTL::PixelFormatInvalid }, // Plane formats depend on specific YCbCr types
            { gfx::TextureAspect::PLANE_1_ONLY, MTL::PixelFormatInvalid },
            { gfx::TextureAspect::PLANE_2_ONLY, MTL::PixelFormatInvalid },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::PixelFormatInvalid;
    }

    MTL::TextureUsage DecodeTextureUsageType(const gfx::TextureUsage& type)
    {
        struct FlagMap {
            gfx::TextureUsage gfxFlag;
            MTL::TextureUsage mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::TextureUsage::COPY_SRC,          MTL::TextureUsageShaderRead },
            { gfx::TextureUsage::COPY_DST,          MTL::TextureUsageShaderRead },
            { gfx::TextureUsage::TEXTURE_BINDING,   MTL::TextureUsageShaderRead },
            { gfx::TextureUsage::STORAGE_BINDING,   MTL::TextureUsageShaderWrite },
            { gfx::TextureUsage::RENDER_ATTACHMENT, MTL::TextureUsageRenderTarget },
            { gfx::TextureUsage::TRANSIENT,         MTL::TextureUsageUnknown }, // No direct transient in Metal
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        MTL::TextureUsage returnFlag = MTL::TextureUsageUnknown;

        bool first = true;
        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                if (first)
                    returnFlag = flag.mtlFlag;
                else
                    returnFlag = static_cast<MTL::TextureUsage>(returnFlag | flag.mtlFlag);

                first = false;
            }
        }

        return returnFlag;
    }

    MTL::BlendFactor DecodeBlendFactorType(const gfx::BlendFactor& type)
    {
        struct FlagMap {
            gfx::BlendFactor gfxFlag;
            MTL::BlendFactor mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::BlendFactor::SRC_ALPHA,           MTL::BlendFactorSourceAlpha },
            { gfx::BlendFactor::ONE_MINUS_SRC_ALPHA, MTL::BlendFactorOneMinusSourceAlpha },
            { gfx::BlendFactor::ONE,                 MTL::BlendFactorOne },
            { gfx::BlendFactor::ZERO,                MTL::BlendFactorZero },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::BlendFactorZero;
    }

    MTL::BlendOperation DecodeBlendOperationType(const gfx::BlendOperation& type)
    {
        struct FlagMap {
            gfx::BlendOperation gfxFlag;
            MTL::BlendOperation mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::BlendOperation::ADD, MTL::BlendOperationAdd },
            { gfx::BlendOperation::SUB, MTL::BlendOperationSubtract },
            { gfx::BlendOperation::MIN, MTL::BlendOperationMin },
            { gfx::BlendOperation::MAX, MTL::BlendOperationMax },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::BlendOperationAdd;
    }

    MTL::StoreAction DecodeStoreOperationType(const gfx::StoreOperation& type)
    {
        struct FlagMap {
            gfx::StoreOperation gfxFlag;
            MTL::StoreAction mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::StoreOperation::STORE,   MTL::StoreActionStore },
            { gfx::StoreOperation::DISCARD, MTL::StoreActionDontCare },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::StoreActionDontCare;
    }

    MTL::LoadAction DecodeLoadOperationType(const gfx::LoadOperation& type)
    {
        struct FlagMap {
            gfx::LoadOperation gfxFlag;
            MTL::LoadAction mtlFlag;
        };

        const FlagMap flagMaping[] =
        {
            { gfx::LoadOperation::CLEAR, MTL::LoadActionClear },
            { gfx::LoadOperation::LOAD,  MTL::LoadActionLoad },
        };

        unsigned int typeValue = static_cast<unsigned int>(type);

        for (const auto& flag : flagMaping)
        {
            if (typeValue & static_cast<unsigned int>(flag.gfxFlag))
            {
                return flag.mtlFlag;
            }
        }

        return MTL::LoadActionDontCare;
    }

    unsigned int DecodeTextureFormatToAlignmentType(const gfx::TextureFormat& type)
    {
        struct FlagMap {
            gfx::TextureFormat gfxFlag;
            unsigned int mtlFlag;
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
                return flag.mtlFlag;
            }
        }

        return 0;
    }
}
