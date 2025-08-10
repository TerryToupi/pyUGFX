#ifndef __VULKAN_WINDOW_HPP__
#define __VULKAN_WINDOW_HPP__

#include <vector>
#include <window.hpp>
#include <vulkanCommon.hpp>
#include <GLFW/glfw3.h>

namespace gfx
{
    class VulkanWindow : public Window
    {
    public:
        virtual void Init(const WindowDescriptor&& desc) override;
        virtual void ShutDown() override;
        virtual void Run(const GameLoop& func) override;
        
        virtual gfx::TextureFormat GetSurfaceFormat() override;
        
        virtual void GetWindowSize(int* width, int* heigh) override;
        
        virtual bool GetKey(input::Key key) override;
        virtual bool GetMouseButton(input::Button button) override;
        virtual void GetMousePos(double* x, double* y) override;
        
        void CreateSurface(VkInstance instance);
        void CleanupSwapchain();
        void CreateSwapchain();
        void ReCreateSwapChain();
        
        GLFWwindow* GetWindow();
        VkSurfaceKHR GetSurface();
        
    private:
        GLFWwindow* m_Window = nullptr;
        VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
        VkSwapchainKHR m_Swapchain = VK_NULL_HANDLE;
        std::vector<VkImage> m_SwapchainImages;
        std::vector<VkImageView> m_SwapchainImageViews;
        VkFormat m_SwapchainImageFormat;
        VkExtent2D m_SwapchainExtent;
    };
}

#endif
