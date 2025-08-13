/// \cond

#ifndef __METAL_WINDOW_HPP__
#define __METAL_WINDOW_HPP__

#include <window.hpp>
#include <metalGlue.hpp>

namespace gfx
{
    class MetalWindow final : public Window
    {
    public:
        virtual void Init(const WindowDescriptor&& desc) override;
        virtual void ShutDown() override;
        virtual void Run(const GameLoop& func) override;
        
        virtual void CreateSwapChain() override;
        virtual void CleanUpSwapChain() override;
        virtual void ReCreateSwapChain() override;
        
        virtual gfx::TextureFormat GetSurfaceFormat() override;
        
        virtual void GetWindowSize(int* width, int* heigh) override;
        
        virtual bool GetKey(input::Key key) override;
        virtual bool GetMouseButton(input::Button button) override;
        virtual void GetMousePos(double* x, double* y) override;
        
        
    private:
        GLFWwindow* m_Window;
        NS::Window* m_NSwindow;
        CA::MetalLayer* m_SwapChain;
    };
}

#endif

/// \endcond
