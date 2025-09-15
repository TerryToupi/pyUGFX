#ifndef __VULKAN_GPU_ALLOCATOR_HPP__
#define __VULKAN_GPU_ALLOCATOR_HPP__

#include<vector>
#include<array>
#include<span.hpp>
#include<assert.hpp>
#include<vulkanCommon.hpp>

namespace gfx
{
	namespace GPUResource
	{
		struct Buffer
		{
			VkBuffer        buffer{};      // Vulkan Buffer
			VmaAllocation   allocation{};  // Memory associated with the buffer
			VkDeviceAddress address{};     // Address of the buffer in the shader
		};

		/*--
		 * An image is a region of memory used to store image data.
		 * It is used to store texture data, framebuffer data, and other types of data.
		-*/
		struct Image
		{
			VkImage       image{};       // Vulkan Image
			VmaAllocation allocation{};  // Memory associated with the image
		};

		/*--
		 * The image resource is an image with an image view and a layout.
		 * and other information like format and extent.
		-*/
		struct ImageResource : Image
		{
			VkImageView   view{};    // Image view
			VkExtent2D    extent{};  // Size of the image
			VkImageLayout layout{};  // Layout of the image (color attachment, shader read, ...)
		};
	}

	namespace GPUAllocator
	{
		// Initialization of VMA allocator.
		void init();

		// De-initialization of VMA allocator.
		void deinit();

		/*-- Create a buffer -*/
		  /*
		   * UBO: VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT
		   *        + VMA_MEMORY_USAGE_CPU_TO_GPU
		   * SSBO: VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
		   *        + VMA_MEMORY_USAGE_CPU_TO_GPU // Use this if the CPU will frequently update the buffer
		   *        + VMA_MEMORY_USAGE_GPU_ONLY // Use this if the CPU will rarely update the buffer
		   *        + VMA_MEMORY_USAGE_GPU_TO_CPU  // Use this when you need to read back data from the SSBO to the CPU
		   *      ----
		   *        + VMA_ALLOCATION_CREATE_MAPPED_BIT // Automatically maps the buffer upon creation
		   *        + VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT // If the CPU will sequentially write to the buffer's memory,
		   */
		GPUResource::Buffer createBuffer(VkDeviceSize             size,
										 VkBufferUsageFlags2KHR   usage,
										 VmaMemoryUsage           memoryUsage = VMA_MEMORY_USAGE_AUTO,
										 VmaAllocationCreateFlags flags = {});


		/*-- Destroy a buffer -*/
		void destroyBuffer(GPUResource::Buffer buffer);

		/*--
		 * Create a staging buffer, copy data into it, and track it.
		 * This method accepts data, handles the mapping, copying, and unmapping
		 * automatically.
		-*/
		GPUResource::Buffer createStagingBuffer(const utils::Span<uint8_t>& data);

		/*--
		 * Create a buffer (GPU only) with data, this is done using a staging buffer
		 * The staging buffer is a buffer that is used to transfer data from the CPU
		 * to the GPU.
		 * and cannot be freed until the data is transferred. So the command buffer
		 * must be submitted, then
		 * the staging buffer can be cleared using the freeStagingBuffers function.
		-*/ 
		GPUResource::Buffer createBufferAndUploadData(utils::Span<uint8_t>& data, 
													  VkBufferUsageFlags2KHR usageFlags);

		/*--
		 * Create an image in GPU memory. This does not adding data to the image.
		 * This is only creating the image in GPU memory.
		 * See createImageAndUploadData for creating an image and uploading data.
		-*/
		GPUResource::Image createImage(const VkImageCreateInfo& imageInfo);


		/*-- Destroy image --*/
		void destroyImage(GPUResource::Image& image);
		void destroyImageResource(GPUResource::ImageResource& imageRessource);


		/*-- Create an image and upload data using a staging buffer --*/
		GPUResource::ImageResource createImageAndUploadData(const utils::Span<uint8_t>& data, 
															const VkImageCreateInfo& _imageInfo,	
															VkImageLayout finalLayout);

		/*-- When leak are reported, set the ID of the leak here --*/
		void setLeakID(uint32_t id);
	}
}

#endif // !__VULKAN_GPU_ALLOCATOR_HPP__
