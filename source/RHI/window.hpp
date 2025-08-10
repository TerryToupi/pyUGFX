#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <common.hpp>
#include <string>
#include <functional>
#include <enums.hpp>

namespace gfx
{ 
    struct WindowDescriptor
    {
        std::string name;
        uint16_t width; 
        uint16_t height;
    };

    class Window
    {
    public: 
        using GameLoop = std::function<void()>;

        static inline sPtr<Window> instance = nullptr;
        
        virtual void Init(const WindowDescriptor&& desc) = 0;
        virtual void ShutDown() = 0;
        virtual void Run(const GameLoop& func) = 0; 

        virtual void CreateSwapChain() = 0;
        virtual void CleanUpSwapChain() = 0;
        virtual void ReCreateSwapChain() = 0;
        virtual gfx::TextureFormat GetSurfaceFormat() = 0;

		virtual void GetWindowSize(int* width, int* heigh) = 0;

		virtual bool GetKey(input::Key key) = 0;
		virtual bool GetMouseButton(input::Button button) = 0;
		virtual void GetMousePos(double* x, double* y) = 0;

    protected:
        WindowDescriptor m_WindowConfig;
        gfx::TextureFormat m_SurfaceFormat = gfx::TextureFormat::UNDEFINED;

    };
}

#endif
