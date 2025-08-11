#import <metalGlue.hpp>

NS::Window* get_ns_window(GLFWwindow* window, CA::MetalLayer* layer)
{
    CALayer* l = (__bridge CALayer*) layer;
    NSWindow* w = glfwGetCocoaWindow(window);
    
    w.contentView.layer = l;
    w.contentView.wantsLayer = YES;
    
    return (__bridge NS::Window*)w;
}
