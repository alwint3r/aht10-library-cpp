#ifndef AHT10_DELAY_HAL_INTERFACE_H
#define AHT10_DELAY_HAL_INTERFACE_H

#include <functional>
#include <cstdint>

namespace AHT10
{
    namespace Platform
    {
        using DelayFunction = std::function<void(uint32_t)>;
    } // namespace Platform
} // namespace AHT10

#endif