#ifndef INES_HEADER_HPP
#define INES_HEADER_HPP

#include <core/io/io.hpp>

#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

namespace core
{
    // ines_header = 16byte
    struct ines_header
    {
        // nes = 4E 45 53 1A (NES magic number)
        uint8_t nes[4];

        // program_rom_count * 16KiB (16384) = program_rom size
        uint8_t program_rom_count;

        // program_rom_count * 8KiB (8192) = charactor_rom size
        uint8_t charactor_rom_count;

        union
        {
            uint8_t flag_6;

            struct
            {
                uint8_t mirroring               : 1;
                uint8_t persisent_memory_exists : 1;
                uint8_t trainer_exists          : 1;
                uint8_t ignore_mirroring        : 1;
                uint8_t mapper_lower            : 4;
            };
        };

        uint8_t flag_7;
        uint8_t flag_8;
        uint8_t flag_9;
        uint8_t flag_10;
        uint8_t padding[5];
    } __attribute__((packed));

    class primitive_rom : public io
    {
      public:
        primitive_rom(std::unique_ptr<std::vector<uint8_t>> target_rom_data);

        uint8_t                     read(address target_address) override;
        void                        write(address target_address, uint8_t data) override;
        const std::vector<uint8_t> &raw_data() const;

        void dump();

      private:
        std::unique_ptr<std::vector<uint8_t>> rom_data;
    };

    class rom
    {
      public:
        rom(const char *file_path);
        ~rom() {};

        ines_header          header;
        std::vector<uint8_t> trainer;
        std::unique_ptr<io>  charactor;
        std::vector<uint8_t> inst_rom;
        std::unique_ptr<io>  program;

        void ines_info();

      private:
        std::ifstream open_rom_file(const char *path);
        ines_header   read_ines_header(std::ifstream &flie);
        void          setup_rom(std::ifstream &file);
        std::unique_ptr<std::vector<uint8_t>>
            create_vector_from_file(std::ifstream &file, std::streamoff offset, size_t size);
    };

}

#endif
