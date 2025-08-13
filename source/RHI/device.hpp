/**
 * @file device.hpp
 * @brief Defines the GPU device abstraction and its descriptor.
 *
 * A Device represents a GPU and its associated driver. It provides
 * information about the vendor, device ID, architecture, and driver version.
 * The Device class serves as a singleton interface for GPU initialization
 * and shutdown.
 *
 * @date 2025-08-13
 * author Terry Toupi
 */

#ifndef __DEVICE_HPP__
#define __DEVICE_HPP__

#include <common.hpp>
#include <string>
#include <cstdint>

namespace gfx
{
    /**
     * @brief Describes a GPU device.
     */
    struct DeviceDescriptor
    {
        uint32_t vendorID = 0;          ///< Vendor identifier (e.g., PCI ID).
        std::string vendor;             ///< Vendor name (e.g., NVIDIA, AMD).
        std::string architecture;       ///< GPU architecture (e.g., Ampere, RDNA2).
        uint32_t deviceID = 0;          ///< Device identifier.
        std::string name;               ///< Human-readable device name.
        std::string driver;             ///< Driver version string.
    };
    
    /**
     * @brief Abstract GPU device interface.
     *
     * This class represents a GPU device and exposes initialization and
     * shutdown methods. The static `instance` pointer allows global access
     * to the current GPU device.
     */
    class Device
    {
    public:
        static inline sPtr<Device> instance = nullptr; ///< Global device instance.
        
        virtual ~Device() = default;
        
        /**
         * @brief Initializes the GPU device.
         */
        virtual void Init() = 0;

        /**
         * @brief Shuts down the GPU device.
         */
        virtual void ShutDown() = 0;

    public:
        DeviceDescriptor p_DeviceDesc; ///< Descriptor for the GPU device.
    };
}

#endif // __DEVICE_HPP__
