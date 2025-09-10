/**
 * @file context.hpp
 * @brief Platform context initialization and teardown for graphics setup.
 *
 * This file contains declarations for platform-specific context management,
 * including platform enumeration and functions for initializing and shutting down
 * the graphics context for supported platforms.
 * 
 * @date 2025-08-13
 * @author Terry Toupi
 */

#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__

/**
 * @namespace setup
 * @brief Namespace for platform setup and context management.
 */
namespace setup
{
    /**
     * @enum Platforms
     * @brief Supported graphics platforms.
     *
     * Enumerates the available graphics platforms for context initialization.
     */
    enum Platforms : unsigned int
    {
        UNDEFINED = 0, /**< Undefined platform (default, no platform selected) */
        VULKAN    = 1, /**< Vulkan platform */
        METAL     = 2  /**< Metal platform */
    };

    /**
     * @brief Initialize the platform context based on the specified platform.
     *
     * Sets up the graphics context for the selected platform.
     *
     * @param platform The platform to initialize. Defaults to Platforms::UNDEFINED.
     */
    void ContextInit(Platforms platform = Platforms::UNDEFINED);

    /**
     * @brief Destroy the platform context.
     *
     * Tears down the graphics context and releases any platform-specific resources.
     */
    void ContextShutDown();
}

#endif // !__CONTEXT_HPP__
