#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdint.h>

namespace core
{
    using address = uint16_t;

    inline static address merge_address(uint8_t lower_address, uint8_t higher_address)
    {
        return static_cast<uint16_t>(lower_address) | static_cast<uint16_t>(higher_address << 8);
    }

    inline static uint8_t convert_lower_half_8(address target_address)
    {
        return (target_address >> 0) & 0xFF;
    }

    inline static uint8_t convert_higher_half_8(address target_address)
    {
        return (target_address >> 8) & 0xFF;
    }

}

#endif
