/**
 * @file commands.hpp
 * @brief Defines data structures and utilities for encoding and decoding GPU draw/dispatch commands.
 *
 * This file contains definitions for Draw and Dispatch command structures, along with
 * helper classes to encode and decode these commands into a compact stream format.
 *
 * Bitmask macros are also provided to track "dirty" state changes in command streams.
 *
 * @date 2025-08-13
 * @author Terry Toupi
 */

#ifndef __COMMANDS_HPP__
#define __COMMANDS_HPP__

#include <handle.hpp>
#include <span.hpp>
#include <resources/shader.hpp>
#include <resources/bindGroup.hpp>
#include <resources/buffer.hpp>
#include <resources/dynamicBuffers.hpp>
#include <vector>

using namespace utils;

/** @brief Sets a bit in a bitmask variable. */
#define SET_BIT(var, bit) ((var) |= (1U << (bit)))

/** @brief Checks if a bit is set in a bitmask variable. */
#define IS_BIT_SET(var, bit) (((var) & (1U << (bit))) != 0)

/** @name Dirty bit flags
 *  @brief Bit positions used for marking dirty states in the draw/dispatch encoder.
 *  @{
 */
#define SHADER_DBIT                 0
#define BINDGROUP0_DBIT              1
#define BINDGROUP1_DBIT              2
#define BINDGROUP2_DBIT              3
#define DYNAMICBUFFER_DBIT           4
#define INDEXBUFFER_DBIT              5
#define VERTEXBUFFER0_DBIT            6
#define VERTEXBUFFER1_DBIT            7
#define VERTEXBUFFER2_DBIT            8
#define INDEXOFFSET_DBIT              9
#define VERTEXOFFSET_DBIT            10
#define INSTANCEOFFSET_DBIT           11
#define INSTANCECOUNT_DBIT            12
#define DYNAMICBUFFEROFFSET0_DBIT    13
#define DYNAMICBUFFEROFFSET1_DBIT    14
#define TRIANGLECOUNT_DBIT           15
/** @} */

namespace gfx
{
    /**
     * @brief Represents a single draw command with associated resources and offsets.
     */
    struct Draw
    {
        Handle<Shader> shader;                 /**< Shader used for the draw call. */
        Handle<BindGroup> bindGroups[3];       /**< Up to three bind groups for resource binding. */
        Handle<DynamicBuffers> dynamicBuffer;  /**< Dynamic buffer resource. */
        Handle<Buffer> indexBuffer;            /**< Index buffer. */
        Handle<Buffer> vertexBuffers[3];       /**< Up to three vertex buffers. */
        uint32_t indexOffset = 0;               /**< Index buffer offset in elements. */
        uint32_t vertexOffset = 0;              /**< Vertex buffer offset in elements. */
        uint32_t instanceOffset = 0;            /**< Instance offset for instanced rendering. */
        uint32_t instanceCount = 1;             /**< Number of instances to draw. */
        uint32_t dynamicBufferOffset[2];        /**< Dynamic buffer offsets. */
        uint32_t triangleCount = 0;             /**< Number of triangles to draw. */
    };

    /**
     * @brief Represents a single compute dispatch command.
     */
    struct Dispatch
    {
        Handle<Shader> shader;                          /**< Shader used for the dispatch call. */
        Handle<BindGroup> bindGroups[3];                /**< Up to three bind groups for resource binding. */
        Handle<DynamicBuffers> dynamicBuffer;           /**< Dynamic buffer resource. */
        uint32_t dynamicBufferOffset[2];                /**< Dynamic buffer offsets. */
        uint32_t threadGroupCount[3] = { 0, 0, 0 };     /**< Thread group counts for X, Y, Z dimensions. */
    };

    /**
	 * @brief Represents a render pass command that's specifying the color targets and the depth target of the pass.
	 */
    struct RenderDescriptor
    {
        /**
         * @brief Represents a single color target attachment.
         */
        struct ColorTarget
        {
            utils::Handle<Texture> target;
            LoadOperation loadOp = LoadOperation::CLEAR;
            StoreOperation storeOp = StoreOperation::STORE;
            double clearColor[4] = {0.2, 0.2, 0.2, 1};
        }; 

        /**
         * @brief Represents swapchain attachment.
         */
        struct SwapChainTarget 
        {
            bool enabled = false;
            LoadOperation loadOp = LoadOperation::CLEAR;
            StoreOperation storeOp = StoreOperation::STORE;
            double clearColor[4] = {0.2, 0.2, 0.2, 1};
        };

        /**
         * @brief Represents a depth/stencil target attachment.
         */
        struct DepthTarget
        {
            bool enabled = false;
            utils::Handle<Texture> target;
            LoadOperation loadOp = LoadOperation::CLEAR;
            StoreOperation storeOp = StoreOperation::STORE;
            LoadOperation stencilLoadOp = LoadOperation::CLEAR;
            StoreOperation stencilStoreOp = StoreOperation::STORE;
            float clearZ = 0.0f;
            uint32_t clearStencil = 0;
        };

        DepthTarget depthTarget;
        SwapChainTarget swapTarget;
        utils::Span<ColorTarget> colorTargets;
    };
}

#endif // !__COMMANDS_HPP__
