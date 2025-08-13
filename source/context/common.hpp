/**
 * @file common.hpp
 * @brief Utility smart pointer aliases and creation functions for graphics code.
 *
 * This file defines convenient type aliases and factory functions for smart pointers
 * in the @ref gfx namespace, to simplify usage of std::unique_ptr and std::shared_ptr
 * throughout graphics-related code.
 * 
 * @date 2025-08-13
 * @author Terry Toupi
 */

#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <memory>

/**
 * @namespace gfx
 * @brief Namespace containing graphics utility types and functions.
 */
namespace gfx
{
    /**
     * @brief Alias for std::unique_ptr.
     * @tparam T Type pointed to.
     */
    template<typename T>
    using uPtr = std::unique_ptr<T>;

    /**
     * @brief Creates a std::unique_ptr for type T.
     * @tparam T Type to construct.
     * @tparam Args Types of constructor arguments.
     * @param args Arguments to forward to T's constructor.
     * @return A std::unique_ptr to an instance of T.
     */
    template<typename T, typename ... Args>
    constexpr uPtr<T> CreateUnique(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    /**
     * @brief Alias for std::shared_ptr.
     * @tparam T Type pointed to.
     */
    template<typename T>
    using sPtr = std::shared_ptr<T>;

    /**
     * @brief Creates a std::shared_ptr for type T.
     * @tparam T Type to construct.
     * @tparam Args Types of constructor arguments.
     * @param args Arguments to forward to T's constructor.
     * @return A std::shared_ptr to an instance of T.
     */
    template<typename T, typename ... Args>
    constexpr sPtr<T> CreateShared(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif // !__COMMON_HPP__
