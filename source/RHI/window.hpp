/**
 * @file Window.hpp
 * @brief Defines the abstract gfx::Window interface and WindowDescriptor struct.
 *
 * Provides a platform-independent interface for creating and managing a window,
 * handling input, and managing the swap chain for rendering.
 * 
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <common.hpp>
#include <string>
#include <functional>
#include <enums.hpp>

namespace gfx
{
    /**
     * @brief Descriptor structure for window configuration.
     *
     * Used to define the initial properties of a window such as
     * its name, width, and height.
     */
    struct WindowDescriptor
    {
        std::string name;   /**< The title of the window. */
        uint16_t width;     /**< The width of the window in pixels. */
        uint16_t height;    /**< The height of the window in pixels. */
    };

    /**
     * @brief Abstract interface for a window in the graphics system.
     *
     * Provides platform-independent functionality for window creation,
     * input handling, and swap chain management.
     * Derived classes must implement all pure virtual methods.
     */
    class Window
    {
    public:
        /// Type alias for the main game loop function.
        using GameLoop = std::function<void()>;

        /// Singleton instance of the window.
        static inline sPtr<Window> instance = nullptr;
        
        /**
         * @brief Initializes the window with the specified descriptor.
         * @param desc A rvalue reference to a WindowDescriptor struct.
         */
        virtual void Init(const WindowDescriptor&& desc) = 0;

        /**
         * @brief Shuts down the window and releases all resources.
         */
        virtual void ShutDown() = 0;

        /**
         * @brief Runs the main loop of the window.
         * @param func The game loop function to execute every frame.
         */
        virtual void Run(const GameLoop& func) = 0;

        /**
         * @brief Creates the swap chain for rendering.
         */
        virtual void CreateSwapChain() = 0;

        /**
         * @brief Cleans up the swap chain resources.
         */
        virtual void CleanUpSwapChain() = 0;

        /**
         * @brief Recreates the swap chain, usually after a resize.
         */
        virtual void ReCreateSwapChain() = 0;

        /**
         * @brief Gets the pixel format of the rendering surface.
         * @return The surface's texture format.
         */
        virtual gfx::TextureFormat GetSurfaceFormat() = 0;

        /**
         * @brief Retrieves the current window size.
         * @param width Pointer to an int to store the width.
         * @param height Pointer to an int to store the height.
         */
        virtual void GetWindowSize(int* width, int* height) = 0;

        /**
         * @brief Checks if a specific key is currently pressed.
         * @param key The key to query.
         * @return true if the key is pressed, false otherwise.
         */
        virtual bool GetKey(input::Key key) = 0;

        /**
         * @brief Checks if a specific mouse button is currently pressed.
         * @param button The mouse button to query.
         * @return true if the button is pressed, false otherwise.
         */
        virtual bool GetMouseButton(input::Button button) = 0;

        /**
         * @brief Gets the current mouse cursor position.
         * @param x Pointer to a double to store the x-coordinate.
         * @param y Pointer to a double to store the y-coordinate.
         */
        virtual void GetMousePos(double* x, double* y) = 0;

    protected:
        WindowDescriptor m_WindowConfig;           /**< Configuration for the window. */
        gfx::TextureFormat m_SurfaceFormat = gfx::TextureFormat::UNDEFINED; /**< Surface format of the window. */
    };
}

#endif
