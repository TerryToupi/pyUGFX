#include <vulkanGPUAllocator.hpp>
#include <vulkanDevice.hpp>

static VmaAllocator allocator{};
static uint32_t leakID = ~0U;

void gfx::GPUAllocator::init()
{
    VulkanDevice* deviceManager = static_cast<VulkanDevice*>(gfx::Device::instance.get());

    VmaAllocatorCreateInfo allocatorInfo{};
    allocatorInfo.device = deviceManager->getDevice();
    allocatorInfo.physicalDevice = deviceManager->getPhysicalDevice();
    allocatorInfo.instance = deviceManager->getInstance();
    allocatorInfo.vulkanApiVersion = deviceManager->getApiVersion();

    // #TODO : VK_EXT_memory_priority ? VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT
    allocatorInfo.flags |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;  // allow querying for the GPU address of a buffer
    allocatorInfo.flags |= VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE4_BIT;
    allocatorInfo.flags |= VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE5_BIT;  // allow using VkBufferUsageFlags2CreateInfoKHR

    // Because we use VMA_DYNAMIC_VULKAN_FUNCTIONS
    const VmaVulkanFunctions functions = {
        .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
        .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
    };
    allocatorInfo.pVulkanFunctions = &functions;
    VK_CHECK(vmaCreateAllocator(&allocatorInfo, &allocator));
}

void gfx::GPUAllocator::deinit()
{
    vmaDestroyAllocator(allocator);
}

gfx::GPUResource::Buffer gfx::GPUAllocator::createBuffer(VkDeviceSize size, 
                                                         VkBufferUsageFlags2KHR usage, 
                                                         VmaMemoryUsage memoryUsage, 
                                                         VmaAllocationCreateFlags flags)
{
    VulkanDevice* deviceManager = (VulkanDevice*)gfx::Device::instance.get();

    // This can be used only with maintenance5
    const VkBufferUsageFlags2CreateInfoKHR bufferUsageFlags2CreateInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_USAGE_FLAGS_2_CREATE_INFO_KHR,
        .usage = usage | VK_BUFFER_USAGE_2_SHADER_DEVICE_ADDRESS_BIT_KHR,
    };

    const VkBufferCreateInfo bufferInfo{
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext = &bufferUsageFlags2CreateInfo,
        .size = size,
        .usage = 0,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,  // Only one queue family will access i
    };

    VmaAllocationCreateInfo allocInfo = { .flags = flags, .usage = memoryUsage };
    const VkDeviceSize      dedicatedMemoryMinSize = 64ULL * 1024;  // 64 KB
    if (size > dedicatedMemoryMinSize)
    {
        allocInfo.flags |= VMA_ALLOCATION_CREATE_DEDICATED_MEMORY_BIT;  // Use dedicated memory for large buffers
    }

    // Create the buffer
    gfx::GPUResource::Buffer    resultBuffer;
    VmaAllocationInfo           allocInfoOut{};
    VK_CHECK(vmaCreateBuffer(allocator, &bufferInfo, &allocInfo, &resultBuffer.buffer, &resultBuffer.allocation, &allocInfoOut));

    // Get the GPU address of the buffer
    const VkBufferDeviceAddressInfo info = { .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
                                            .buffer = resultBuffer.buffer };
    resultBuffer.address = vkGetBufferDeviceAddress(deviceManager->getDevice(), &info);

    {  // Find leaks
        static uint32_t counter = 0U;
        if (leakID == counter)
        {
#if defined(_MSVC_LANG)
            __debugbreak();
#endif
        }
        std::string allocID = std::string("allocID: ") + std::to_string(counter++);
        vmaSetAllocationName(allocator, resultBuffer.allocation, allocID.c_str());
    }

    return resultBuffer;
}

void gfx::GPUAllocator::destroyBuffer(GPUResource::Buffer buffer)
{
    vmaDestroyBuffer(allocator, buffer.buffer, buffer.allocation);
}

gfx::GPUResource::Buffer gfx::GPUAllocator::createStagingBuffer(const utils::Span<uint8_t>& data)
{
    const VkDeviceSize bufferSize = data.size();

    // Create a staging buffer
    gfx::GPUResource::Buffer stagingBuffer = createBuffer(bufferSize, 
                                                          VK_BUFFER_USAGE_2_TRANSFER_SRC_BIT_KHR, 
                                                          VMA_MEMORY_USAGE_CPU_TO_GPU,
                                                          VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT);

    // Map and copy data to the staging buffer
    void* cpyData;
    vmaMapMemory(allocator, stagingBuffer.allocation, &cpyData);
    memcpy(cpyData, data.data(), (size_t)bufferSize);
    vmaUnmapMemory(allocator, stagingBuffer.allocation);
    return stagingBuffer;
}

gfx::GPUResource::Buffer gfx::GPUAllocator::createBufferAndUploadData(utils::Span<uint8_t>& data, 
                                                                      VkBufferUsageFlags2KHR usageFlags)
{
    VulkanDevice* deviceManager = (VulkanDevice*)gfx::Device::instance.get();

    // Create staging buffer and upload data
    gfx::GPUResource::Buffer stagingBuffer = createStagingBuffer(data);

    // Create the final buffer in GPU memory
    const VkDeviceSize bufferSize = data.size();
    gfx::GPUResource::Buffer buffer = createBuffer(bufferSize, 
                                                   usageFlags | VK_BUFFER_USAGE_2_TRANSFER_DST_BIT_KHR, 
                                                   VMA_MEMORY_USAGE_GPU_ONLY);

    const std::array<VkBufferCopy, 1> copyRegion{ {{.size = bufferSize}} };

    VkCommandBuffer cmd = deviceManager->beginTransientRecording();
    vkCmdCopyBuffer(cmd, stagingBuffer.buffer, buffer.buffer, uint32_t(copyRegion.size()), copyRegion.data());
    deviceManager->endTransientRecording(cmd);

    destroyBuffer(stagingBuffer);
    return buffer;
}

gfx::GPUResource::Image gfx::GPUAllocator::createImage(const VkImageCreateInfo& imageInfo)
{
    const VmaAllocationCreateInfo createInfo{ .usage = VMA_MEMORY_USAGE_GPU_ONLY };

    gfx::GPUResource::Image image;
    VmaAllocationInfo       allocInfo{};
    VK_CHECK(vmaCreateImage(allocator, &imageInfo, &createInfo, &image.image, &image.allocation, &allocInfo));
    return image;
}

void gfx::GPUAllocator::destroyImage(GPUResource::Image& image)
{
    vmaDestroyImage(allocator, image.image, image.allocation);
}

void gfx::GPUAllocator::destroyImageResource(GPUResource::ImageResource& imageRessource)
{
    VulkanDevice* deviceManager = (VulkanDevice*)(gfx::Device::instance.get());

    gfx::GPUAllocator::destroyImage(imageRessource);
    vkDestroyImageView(deviceManager->getDevice(), imageRessource.view, nullptr);
}

gfx::GPUResource::ImageResource gfx::GPUAllocator::createImageAndUploadData(const utils::Span<uint8_t>& data, 
                                                                            const VkImageCreateInfo& _imageInfo, 
                                                                            VkImageLayout finalLayout)
{
    VulkanDevice* deviceManager = (VulkanDevice*)(gfx::Device::instance.get());

    // Create staging buffer and upload data
    gfx::GPUResource::Buffer stagingBuffer = createStagingBuffer(data);

    // Create image in GPU memory
    VkImageCreateInfo imageInfo = _imageInfo;
    imageInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;  // We will copy data to this image
    gfx::GPUResource::Image image = createImage(imageInfo);

    VkCommandBuffer cmd = deviceManager->beginTransientRecording();
    // Transition image layout for copying data
    deviceManager->cmdTransitionImageLayout(cmd, image.image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    // Copy buffer data to the image
    const std::array<VkBufferImageCopy, 1> copyRegion{
        {{.imageSubresource = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT, .layerCount = 1}, .imageExtent = imageInfo.extent}} };

    vkCmdCopyBufferToImage(cmd, stagingBuffer.buffer, image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
        uint32_t(copyRegion.size()), copyRegion.data());

    // Transition image layout to final layout
    deviceManager->cmdTransitionImageLayout(cmd, image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, finalLayout);
    deviceManager->endTransientRecording(cmd);

    gfx::GPUResource::ImageResource resultImage(image);
    resultImage.layout = finalLayout;

    destroyBuffer(stagingBuffer);
    return resultImage;
}

void gfx::GPUAllocator::setLeakID(uint32_t id)
{
    leakID = id;
}

