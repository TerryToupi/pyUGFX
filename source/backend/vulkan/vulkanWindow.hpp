/// \cond

#ifndef __VULKAN_WINDOW_HPP__
#define __VULKAN_WINDOW_HPP__

#include <vector>
#include <array>
#include <log.hpp>
#include <assert.hpp>
#include <window.hpp>
#include <vulkanCommon.hpp>
#include <vulkanDevice.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace gfx
{
    class Swapchain
    {
    public:
        Swapchain() = default;
        ~Swapchain() { ASSERT(m_swapChain == VK_NULL_HANDLE, "Missing ShutDown()!"); }

        void        requestRebuild() { m_needRebuild = true; }
        bool        needRebuilding() const { return m_needRebuild; }
        VkImage     getImage() const { return m_nextImages[m_frameImageIndex].image; }
        VkImageView getImageView() const { return m_nextImages[m_frameImageIndex].imageView; }
        VkFormat    getImageFormat() const { return m_imageFormat; }
        uint32_t    getMaxFramesInFlight() const { return m_maxFramesInFlight; }
        VkSemaphore getImageAvailableSemaphore() const
        {
            return m_frameResources[m_frameResourceIndex].imageAvailableSemaphore;
        }
        VkSemaphore getRenderFinishedSemaphore() const { return m_frameResources[m_frameImageIndex].renderFinishedSemaphore; }

        void init();
        void destroy();

        VkExtent2D initResources(bool vSync = true);
        VkExtent2D reinitResources(bool vSync = true);
        void deinitResources();

        VkResult acquireNextImage();
        void presentFrame(VkQueue queue);

    private:
        // Represents an image within the swapchain that can be rendered to.
        struct Image
        {
            VkImage     image{};      // Image to render to
            VkImageView imageView{};  // Image view to access the image
        };
        /*--
         * Resources associated with each frame being processed.
         * Each frame has its own set of resources, mainly synchronization primitives
        -*/
        struct FrameResources
        {
            VkSemaphore imageAvailableSemaphore{};  // Signals when the image is ready for rendering
            VkSemaphore renderFinishedSemaphore{};  // Signals when rendering is finished
        };

        VkSurfaceFormat2KHR selectSwapSurfaceFormat(const std::vector<VkSurfaceFormat2KHR>& availableFormats) const;
        VkPresentModeKHR selectSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes, bool vSync = true);

    private:
        VkSwapchainKHR   m_swapChain{};       // The swapchain
        VkFormat         m_imageFormat{};     // The format of the swapchain images
        VkSurfaceKHR     m_surface{};         // The surface to present images to

        std::vector<Image>          m_nextImages{};
        std::vector<FrameResources> m_frameResources{};
        uint32_t                    m_frameResourceIndex = 0;
        uint32_t                    m_frameImageIndex = 0;
        bool                        m_needRebuild = false;

        uint32_t m_maxFramesInFlight = 3;  // Best for pretty much all cases
    };



    class VulkanWindow final : public Window
    {
    public:
        virtual void Init(const WindowDescriptor&& desc) override;
        virtual void ShutDown() override;
        virtual void Run(const GameLoop& func) override;
        
        virtual gfx::TextureFormat GetSurfaceFormat() override;
        
        virtual bool GetWindowVSync() override;
        virtual void GetWindowSize(int* width, int* height) override;
        
        virtual bool GetKey(input::Key key) override;
        virtual bool GetMouseButton(input::Button button) override;
        virtual void GetMousePos(double* x, double* y) override;

        void SetWindowSize(int width, int height);

    public:
        /*--
		 * Vulkan should have full acces to the swapchain
        -*/
        Swapchain swapChain;
        
    private:
        GLFWwindow* m_window;

        friend class Swapchain;
    };
}

#endif

/// \endcond
