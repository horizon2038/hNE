#ifndef INES_HEADER_HPP
#define INES_HEADER_HPP

#include <stdint.h>
#include <vector>

namespace core
{
    struct ines_header 
    {
        uint8_t nes[4];

        // program_rom_size * 16KiB (16384) = result
        uint8_t program_rom_size;

        // program_rom_size * 8KiB (8192) = result
        uint8_t charactor_rom_size;

        union
        {
            uint8_t flag_6;
            struct
            {
                uint8_t mirroring : 1;
                uint8_t persisent_memory_exists : 1;
                uint8_t trainer_exists : 1;
                uint8_t ignore_mirroring : 1;
                uint8_t mapper_lower : 4;
            };
        };

        uint8_t flag_7;
        uint8_t flag_8;
        uint8_t flag_9;
        uint8_t flag_10;
        uint8_t padding[5];
    } __attribute__((packed));

    struct rom
    {
        ines_header _header;
        std::vector<uint8_t> _trainer;
        std::vector<uint8_t> _program_rom;
        std::vector<uint8_t> _charactor_rom;
        std::vector<uint8_t> _inst_rom;
        std::vector<uint8_t> _p_rom;
    };
}

#endif
