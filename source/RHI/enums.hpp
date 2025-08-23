/**
 * @file enums.hpp
 * @brief Enumerations for input and graphics systems.
 *
 * This file defines strongly-typed enumerations used for keyboard and mouse input (namespace @ref input)
 * and for graphics API abstractions (namespace @ref gfx), such as shader stages, buffer types, texture formats, and rendering states.
 * It also provides bitwise operator overloads for select enums to facilitate flag/mask usage.
 * 
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

#include <cstdint>

/**
 * @brief Macro for left bit-shift of unsigned integers.
 *
 * This macro is used to generate bitmask values for enum entries.
 *
 * @param x Number of positions to shift.
 * @return Result of shifting 1u by x positions.
 */
#define UINT_BIT_SHIFT(x) (1u << x)

/**
 * @namespace input
 * @brief Namespace containing input-related enumerations.
 */
namespace input
{
    /**
     * @enum Key
     * @brief Enumeration for keyboard keys.
     *
     * Key codes are assigned using ASCII values for printable characters and
     * specific integer values for non-printable keys.
     */
    enum class Key : unsigned
    {
        SPACE              = 32,  /**< Space key */
        APOSTROPHE         = 39,  /**< Apostrophe key (') */
        COMMA              = 44,  /**< Comma key (,) */
        MINUS              = 45,  /**< Minus key (-) */
        PERIOD             = 46,  /**< Period key (.) */
        SLASH              = 47,  /**< Slash key (/) */
        NUM_0              = 48,  /**< Number 0 key */
        NUM_1              = 49,  /**< Number 1 key */
        NUM_2              = 50,  /**< Number 2 key */
        NUM_3              = 51,  /**< Number 3 key */
        NUM_4              = 52,  /**< Number 4 key */
        NUM_5              = 53,  /**< Number 5 key */
        NUM_6              = 54,  /**< Number 6 key */
        NUM_7              = 55,  /**< Number 7 key */
        NUM_8              = 56,  /**< Number 8 key */
        NUM_9              = 57,  /**< Number 9 key */
        SEMICOLON          = 59,  /**< Semicolon key (;) */
        EQUAL              = 61,  /**< Equal key (=) */
        A                  = 65,  /**< A key */
        B                  = 66,  /**< B key */
        C                  = 67,  /**< C key */
        D                  = 68,  /**< D key */
        E                  = 69,  /**< E key */
        F                  = 70,  /**< F key */
        G                  = 71,  /**< G key */
        H                  = 72,  /**< H key */
        I                  = 73,  /**< I key */
        J                  = 74,  /**< J key */
        K                  = 75,  /**< K key */
        L                  = 76,  /**< L key */
        M                  = 77,  /**< M key */
        N                  = 78,  /**< N key */
        O                  = 79,  /**< O key */
        P                  = 80,  /**< P key */
        Q                  = 81,  /**< Q key */
        R                  = 82,  /**< R key */
        S                  = 83,  /**< S key */
        T                  = 84,  /**< T key */
        U                  = 85,  /**< U key */
        V                  = 86,  /**< V key */
        W                  = 87,  /**< W key */
        X                  = 88,  /**< X key */
        Y                  = 89,  /**< Y key */
        Z                  = 90,  /**< Z key */
        LEFT_BRACKET       = 91,  /**< Left bracket key ([) */
        BACKSLASH          = 92,  /**< Backslash key (\) */
        RIGHT_BRACKET      = 93,  /**< Right bracket key (]) */
        GRAVE_ACCENT       = 96,  /**< Grave accent key (`) */
        WORLD_1            = 161, /**< Non-US #1 key */
        WORLD_2            = 162, /**< Non-US #2 key */
    };

    /**
     * @enum Button
     * @brief Enumeration for mouse buttons.
     */
    enum class Button : unsigned
    {
        BUTTON_1        = 0, /**< Mouse button 1 (usually left) */
        BUTTON_2        = 1, /**< Mouse button 2 (usually right) */
        BUTTON_3        = 2, /**< Mouse button 3 (usually middle) */
        BUTTON_4        = 3, /**< Mouse button 4 */
        BUTTON_5        = 4, /**< Mouse button 5 */
        BUTTON_6        = 5, /**< Mouse button 6 */
        BUTTON_7        = 6, /**< Mouse button 7 */
        BUTTON_8        = 7, /**< Mouse button 8 */
        BUTTON_LAST     = 7, /**< The last mouse button available */
        BUTTON_LEFT     = 0, /**< Left mouse button */
        BUTTON_RIGHT    = 1, /**< Right mouse button */
        BUTTON_MIDDLE   = 2, /**< Middle mouse button */
    };
}

/**
 * @namespace gfx
 * @brief Namespace containing graphics-related enumerations and operators.
 */
namespace gfx
{
    /**
     * @enum ShaderStage
     * @brief Stages of a GPU shader pipeline.
     */
    enum class ShaderStage : unsigned int
    {
        VERTEX   = UINT_BIT_SHIFT(0), /**< Vertex shader stage */
        FRAGMENT = UINT_BIT_SHIFT(1), /**< Fragment shader stage */
        COMPUTE  = UINT_BIT_SHIFT(2), /**< Compute shader stage */
    };

    /**
     * @enum ShaderPipelineType
     * @brief Types of shader pipelines.
     */
    enum class ShaderPipelineType : unsigned int
    {
        GRAPHICS = UINT_BIT_SHIFT(0), /**< Graphics pipeline */
        COMPUTE  = UINT_BIT_SHIFT(1)  /**< Compute pipeline */
    };

    /**
     * @enum BufferBindingType
     * @brief Types of buffer bindings.
     */
    enum class BufferBindingType : unsigned int
    {
        UNIFORM                = UINT_BIT_SHIFT(0), /**< Uniform buffer */
        UNIFORM_DYNAMIC_OFFSET = UINT_BIT_SHIFT(1), /**< Uniform buffer with dynamic offset */
        STORAGE                = UINT_BIT_SHIFT(2), /**< Storage buffer */
        READ_ONLY_STORAGE      = UINT_BIT_SHIFT(3), /**< Read-only storage buffer */
        READ_WRITE_STORAGE     = UINT_BIT_SHIFT(4), /**< Read-write storage buffer */
    };

    /**
     * @enum Compare
     * @brief Comparison functions for depth/stencil tests.
     */
    enum class Compare : unsigned int
    {
        NEVER            = UINT_BIT_SHIFT(0), /**< Never passes */
        LESS             = UINT_BIT_SHIFT(1), /**< Passes if incoming value is less */
        LESS_OR_EQUAL    = UINT_BIT_SHIFT(2), /**< Passes if incoming value is less or equal */
        GREATER          = UINT_BIT_SHIFT(3), /**< Passes if incoming value is greater */
        GREATER_OR_EQUAL = UINT_BIT_SHIFT(4), /**< Passes if incoming value is greater or equal */
        EQUAL            = UINT_BIT_SHIFT(5), /**< Passes if incoming value is equal */
        NOT_EQUAL        = UINT_BIT_SHIFT(6), /**< Passes if incoming value is not equal */
        ALAWAYS          = UINT_BIT_SHIFT(7), /**< Always passes (Note: typo, should be ALWAYS) */
        UNDEFINED        = UINT_BIT_SHIFT(8)  /**< Undefined comparison */
    };

    /**
     * @enum VertexFormat
     * @brief Vertex attribute formats.
     */
    enum class VertexFormat : unsigned int
    {
        F16      = UINT_BIT_SHIFT(0),  /**< 16-bit float */
        F16x2    = UINT_BIT_SHIFT(1),  /**< 2x 16-bit float */
        F16x4    = UINT_BIT_SHIFT(2),  /**< 4x 16-bit float */
        I16      = UINT_BIT_SHIFT(3),  /**< 16-bit signed int */
        I16x2    = UINT_BIT_SHIFT(4),  /**< 2x 16-bit signed int */
        I16x4    = UINT_BIT_SHIFT(5),  /**< 4x 16-bit signed int */
        U16      = UINT_BIT_SHIFT(6),  /**< 16-bit unsigned int */
        U16x2    = UINT_BIT_SHIFT(7),  /**< 2x 16-bit unsigned int */
        U16x4    = UINT_BIT_SHIFT(8),  /**< 4x 16-bit unsigned int */
        F32      = UINT_BIT_SHIFT(9),  /**< 32-bit float */
        F32x2    = UINT_BIT_SHIFT(10), /**< 2x 32-bit float */
        F32x3    = UINT_BIT_SHIFT(11), /**< 3x 32-bit float */
        F32x4    = UINT_BIT_SHIFT(12), /**< 4x 32-bit float */
        I32      = UINT_BIT_SHIFT(13), /**< 32-bit signed int */
        I32x2    = UINT_BIT_SHIFT(14), /**< 2x 32-bit signed int */
        I32x3    = UINT_BIT_SHIFT(15), /**< 3x 32-bit signed int */
        I32x4    = UINT_BIT_SHIFT(16), /**< 4x 32-bit signed int */
        U32      = UINT_BIT_SHIFT(17), /**< 32-bit unsigned int */
        U32x2    = UINT_BIT_SHIFT(18), /**< 2x 32-bit unsigned int */
        U32x3    = UINT_BIT_SHIFT(19), /**< 3x 32-bit unsigned int */
        U32x4    = UINT_BIT_SHIFT(20), /**< 4x 32-bit unsigned int */
        UNORM8   = UINT_BIT_SHIFT(21), /**< 8-bit unsigned normalized */
        UNORM8x2 = UINT_BIT_SHIFT(22), /**< 2x 8-bit unsigned normalized */
        UNORM8x4 = UINT_BIT_SHIFT(23)  /**< 4x 8-bit unsigned normalized */
    };

    /**
     * @enum Filter
     * @brief Texture filtering modes.
     */
    enum class Filter : unsigned int
    {
        NEAREST = UINT_BIT_SHIFT(0), /**< Nearest neighbor filtering */
        LINEAR  = UINT_BIT_SHIFT(1), /**< Linear filtering */
        CUBIC   = UINT_BIT_SHIFT(2), /**< Cubic filtering */
    };

    /**
     * @enum Wrap
     * @brief Texture wrapping modes.
     */
    enum class Wrap : unsigned int
    {
        REPEAT              = UINT_BIT_SHIFT(0), /**< Repeat texture */
        REPEAT_MIRRORED     = UINT_BIT_SHIFT(1), /**< Mirrored repeat */
        CLAMP_TO_EDGE       = UINT_BIT_SHIFT(2), /**< Clamp to edge */
        CLAMP_TO_BORDER     = UINT_BIT_SHIFT(3), /**< Clamp to border */
        MIRROR_CLAMP_TO_EDGE= UINT_BIT_SHIFT(4), /**< Mirror clamp to edge */
    };

    /**
     * @enum Topology
     * @brief Primitive topology types for vertex data.
     */
    enum class Topology : unsigned int
    {
        POINT_LIST      = UINT_BIT_SHIFT(0), /**< Point list */
        LINE_LIST       = UINT_BIT_SHIFT(1), /**< Line list */
        LINE_STRIP      = UINT_BIT_SHIFT(2), /**< Line strip */
        TRIANGLE_LIST   = UINT_BIT_SHIFT(3), /**< Triangle list */
        TRIANGLE_STRIP  = UINT_BIT_SHIFT(4), /**< Triangle strip */
        TRIANGLE_FAN    = UINT_BIT_SHIFT(5), /**< Triangle fan */
        PATCH_LIST      = UINT_BIT_SHIFT(6), /**< Patch list */
    };

    /**
     * @enum PolygonMode
     * @brief Polygon rendering modes.
     */
    enum class PolygonMode : unsigned int
    {
        FILL  = UINT_BIT_SHIFT(0), /**< Fill polygons */
        LINE  = UINT_BIT_SHIFT(1), /**< Draw polygons as lines */
        POINT = UINT_BIT_SHIFT(2), /**< Draw polygons as points */
    };

    /**
     * @enum CullMode
     * @brief Face culling modes.
     */
    enum class CullMode : unsigned int
    {
        NONE           = UINT_BIT_SHIFT(0), /**< No culling */
        FRONT_FACE     = UINT_BIT_SHIFT(1), /**< Cull front faces */
        BACK_FACE      = UINT_BIT_SHIFT(2), /**< Cull back faces */
        FRONT_AND_BACK = UINT_BIT_SHIFT(3), /**< Cull both front and back faces */
    };

    /**
     * @enum TextureFormat
     * @brief Supported texture formats.
     */
    enum class TextureFormat : unsigned int
    {
        RGBA32_FLOAT        = UINT_BIT_SHIFT(0),  /**< 32-bit float RGBA */
        D32_FLOAT           = UINT_BIT_SHIFT(1),  /**< 32-bit float depth */
        RGBA16_FLOAT        = UINT_BIT_SHIFT(2),  /**< 16-bit float RGBA */
        RGBA8_UNORM         = UINT_BIT_SHIFT(3),  /**< 8-bit unsigned normalized RGBA */
        RG16_FLOAT          = UINT_BIT_SHIFT(4),  /**< 16-bit float RG */
        R32_FLOAT           = UINT_BIT_SHIFT(5),  /**< 32-bit float R */
        RGBA8_UNORM_SRGB    = UINT_BIT_SHIFT(6),  /**< 8-bit unsigned normalized RGBA (sRGB) */
        RGBA8_LINEAR        = UINT_BIT_SHIFT(7),  /**< 8-bit linear RGBA */
        BGRA8_UNORM         = UINT_BIT_SHIFT(8),  /**< 8-bit unsigned normalized BGRA */
        BGRA8_UNORM_SRGB    = UINT_BIT_SHIFT(9),  /**< 8-bit unsigned normalized BGRA (sRGB) */
        RG32_FLOAT          = UINT_BIT_SHIFT(10), /**< 32-bit float RG */
        R16_FLOAT           = UINT_BIT_SHIFT(11), /**< 16-bit float R */
        D24_STENCIL_8       = UINT_BIT_SHIFT(12), /**< 24-bit depth + 8-bit stencil */
        D32_FLOAT_STENCIL_8 = UINT_BIT_SHIFT(13), /**< 32-bit float depth + 8-bit stencil */
        D24_PLUS            = UINT_BIT_SHIFT(14), /**< 24-bit depth (plus) */
        D16_UNORM           = UINT_BIT_SHIFT(15), /**< 16-bit unsigned normalized depth */
        UNDEFINED           = UINT_BIT_SHIFT(16)  /**< Undefined format */
    };

    /**
     * @enum TextureSampleType
     * @brief Types of texture samples.
     */
    enum class TextureSampleType : unsigned int
    {
        UNDEFINED        = UINT_BIT_SHIFT(0), /**< Undefined sample type */
        FLOAT            = UINT_BIT_SHIFT(1), /**< Floating-point sample type */
        FLOAT_NO_FILTER  = UINT_BIT_SHIFT(2), /**< Floating-point sample type (no filtering) */
        DEPTH            = UINT_BIT_SHIFT(3), /**< Depth sample type */
        SINT             = UINT_BIT_SHIFT(4), /**< Signed integer sample type */
        UINT             = UINT_BIT_SHIFT(5)  /**< Unsigned integer sample type */
    };

    /**
     * @enum MemoryUsage
     * @brief Memory usage patterns for buffers and textures.
     */
    enum class MemoryUsage : unsigned int
    {
        CPU_ONLY = UINT_BIT_SHIFT(0), /**< CPU-only memory */
        GPU_ONLY = UINT_BIT_SHIFT(1), /**< GPU-only memory */
        GPU_CPU  = UINT_BIT_SHIFT(2), /**< GPU then CPU memory */
        CPU_GPU  = UINT_BIT_SHIFT(3), /**< CPU then GPU memory */
    };

    /**
     * @enum BufferUsage
     * @brief Usage patterns for GPU buffers.
     */
    enum class BufferUsage : unsigned int
    {
        MAP_READ       = UINT_BIT_SHIFT(0), /**< Buffer can be mapped for reading */
        MAP_WRITE      = UINT_BIT_SHIFT(1), /**< Buffer can be mapped for writing */
        COPY_SRC       = UINT_BIT_SHIFT(2), /**< Buffer used as source for copy */
        COPY_DST       = UINT_BIT_SHIFT(3), /**< Buffer used as destination for copy */
        INDEX          = UINT_BIT_SHIFT(4), /**< Buffer used for indices */
        VERTEX         = UINT_BIT_SHIFT(5), /**< Buffer used for vertices */
        UNIFORM        = UINT_BIT_SHIFT(6), /**< Buffer used as uniform */
        STORAGE        = UINT_BIT_SHIFT(7), /**< Buffer used as storage */
        INDIRECT       = UINT_BIT_SHIFT(8), /**< Buffer used for indirect drawing */
        QUERY_RESOLVE  = UINT_BIT_SHIFT(9), /**< Buffer used for query resolve */
    };

    /**
     * @enum BufferUsageHint
     * @brief Usage hints for buffer allocation.
     */
    enum class BufferUsageHint : unsigned int
    {
        STATIC  = UINT_BIT_SHIFT(0), /**< Static buffer */
        DYNAMIC = UINT_BIT_SHIFT(1), /**< Dynamic buffer */
    };

    /**
     * @enum TextureType
     * @brief Texture dimensionality types.
     */
    enum class TextureType : unsigned int
    {
        D1 = UINT_BIT_SHIFT(0), /**< 1D texture */
        D2 = UINT_BIT_SHIFT(1), /**< 2D texture */
        D3 = UINT_BIT_SHIFT(2), /**< 3D texture */
    };

    /**
     * @enum TextureDimention
     * @brief Texture dimension types (including array and cube).
     */
    enum class TextureDimention : unsigned int
    {
        D1          = UINT_BIT_SHIFT(0), /**< 1D */
        D2          = UINT_BIT_SHIFT(1), /**< 2D */
        D2_ARRAY    = UINT_BIT_SHIFT(2), /**< 2D array */
        CUBE        = UINT_BIT_SHIFT(3), /**< Cube */
        CUBE_ARRAY  = UINT_BIT_SHIFT(4), /**< Cube array */
        D3          = UINT_BIT_SHIFT(5)  /**< 3D */
    };

    /**
     * @enum TextureAspect
     * @brief Texture aspect types.
     */
    enum class TextureAspect : unsigned int
    {
        NONE          = UINT_BIT_SHIFT(0), /**< No aspect */
        ALL           = UINT_BIT_SHIFT(1), /**< All aspects */
        STENCIL_ONLY  = UINT_BIT_SHIFT(2), /**< Stencil only */
        DEPTH_ONLY    = UINT_BIT_SHIFT(3), /**< Depth only */
        PLANE_0_ONLY  = UINT_BIT_SHIFT(4), /**< Plane 0 only */
        PLANE_1_ONLY  = UINT_BIT_SHIFT(5), /**< Plane 1 only */
        PLANE_2_ONLY  = UINT_BIT_SHIFT(6)  /**< Plane 2 only */
    };

    /**
     * @enum TextureUsage
     * @brief Usage patterns for textures.
     */
    enum class TextureUsage : unsigned int
    {
        COPY_SRC          = UINT_BIT_SHIFT(0), /**< Used as copy source */
        COPY_DST          = UINT_BIT_SHIFT(1), /**< Used as copy destination */
        TEXTURE_BINDING   = UINT_BIT_SHIFT(2), /**< Used for texture binding */
        STORAGE_BINDING   = UINT_BIT_SHIFT(3), /**< Used for storage binding */
        RENDER_ATTACHMENT = UINT_BIT_SHIFT(4), /**< Used as render attachment */
        TRANSIENT         = UINT_BIT_SHIFT(5), /**< Transient usage */
    };

    /**
     * @enum BlendOperation
     * @brief Blend operations for color blending.
     */
    enum class BlendOperation : unsigned int
    {
        ADD = UINT_BIT_SHIFT(0), /**< Add blending */
        SUB = UINT_BIT_SHIFT(1), /**< Subtract blending */
        MIN = UINT_BIT_SHIFT(2), /**< Minimum blending */
        MAX = UINT_BIT_SHIFT(3), /**< Maximum blending */
    };

    /**
     * @enum BlendFactor
     * @brief Blend factors for color blending.
     */
    enum class BlendFactor : unsigned int
    {
        SRC_ALPHA           = UINT_BIT_SHIFT(0), /**< Source alpha */
        ONE_MINUS_SRC_ALPHA = UINT_BIT_SHIFT(1), /**< One minus source alpha */
        ONE                 = UINT_BIT_SHIFT(2), /**< One */
        ZERO                = UINT_BIT_SHIFT(3), /**< Zero */
    };

    /**
     * @enum StoreOperation
     * @brief Operations for storing render target output.
     */
    enum class StoreOperation : unsigned int
    {
        STORE     = UINT_BIT_SHIFT(0), /**< Store content */
        DISCARD   = UINT_BIT_SHIFT(1), /**< Discard content */
        DONT_CARE = UINT_BIT_SHIFT(2), /**< Don't care */
    };

    /**
     * @enum LoadOperation
     * @brief Operations for loading render target content.
     */
    enum class LoadOperation : unsigned int
    {
        CLEAR     = UINT_BIT_SHIFT(0), /**< Clear content */
        LOAD      = UINT_BIT_SHIFT(1), /**< Load content */
        DONT_CARE = UINT_BIT_SHIFT(2), /**< Don't care */
    };

    /**
     * @enum CommandBufferState
     * @brief States of GPU command buffers.
     */
    enum class CommandBufferState : unsigned int
    {
        EMPTY          = UINT_BIT_SHIFT(0), /**< Empty command buffer */
        CAPTURED       = UINT_BIT_SHIFT(1), /**< Command buffer has recorded commands */
        PENDING_UPLOAD = UINT_BIT_SHIFT(2), /**< Command buffer pending upload */
        UPLOADED       = UINT_BIT_SHIFT(3), /**< Command buffer uploaded */
    };

    /**
     * @enum CommandBufferType
     * @brief Types of GPU command buffers.
     */
    enum class CommandBufferType : unsigned int
    {
        OFFSCREEN = UINT_BIT_SHIFT(0), /**< Offscreen command buffer */
        MAIN      = UINT_BIT_SHIFT(1), /**< Main command buffer */
        POST      = UINT_BIT_SHIFT(2), /**< Post-processing command buffer */
        UI        = UINT_BIT_SHIFT(3), /**< UI command buffer */
    };

    /**
     * @brief Bitwise OR operator for ShaderStage enum.
     * @param lhs Left-hand side ShaderStage.
     * @param rhs Right-hand side ShaderStage.
     * @return Result of bitwise OR operation as ShaderStage.
     */
    inline gfx::ShaderStage operator|(gfx::ShaderStage lhs, gfx::ShaderStage rhs)
    {
        return static_cast<gfx::ShaderStage>(
            static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
        );
    }

    /**
     * @brief Bitwise OR operator for BufferUsage enum.
     * @param lhs Left-hand side BufferUsage.
     * @param rhs Right-hand side BufferUsage.
     * @return Result of bitwise OR operation as BufferUsage.
     */
    inline gfx::BufferUsage operator|(gfx::BufferUsage lhs, gfx::BufferUsage rhs)
    {
        return static_cast<gfx::BufferUsage>(
            static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
        );
    }

    /**
     * @brief Bitwise OR operator for BufferUsageHint enum.
     * @param lhs Left-hand side BufferUsageHint.
     * @param rhs Right-hand side BufferUsageHint.
     * @return Result of bitwise OR operation as BufferUsageHint.
     */
    inline gfx::BufferUsageHint operator|(gfx::BufferUsageHint lhs, gfx::BufferUsageHint rhs)
    {
        return static_cast<gfx::BufferUsageHint>(
            static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
        );
    }

    /**
     * @brief Bitwise OR operator for TextureUsage enum.
     * @param lhs Left-hand side TextureUsage.
     * @param rhs Right-hand side TextureUsage.
     * @return Result of bitwise OR operation as TextureUsage.
     */
    inline gfx::TextureUsage operator|(gfx::TextureUsage lhs, gfx::TextureUsage rhs)
    {
        return static_cast<gfx::TextureUsage>(
            static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)
        );
    }
}

#endif // !__ENUMS_HPP__
