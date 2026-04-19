#include <core/io/memory/rom.hpp>

#include <cstddef>
#include <fstream>
#include <memory>
#include <utility>

#include <stdio.h>

namespace core
{
    primitive_rom::primitive_rom(
        std::unique_ptr<std::vector<uint8_t>> target_rom_data
    )
        : rom_data(std::move(target_rom_data))
    {
        // dump();
    }

    uint8_t primitive_rom::read(address target_address)
    {
        auto rom_size = rom_data->size();
        if (rom_size == 0)
        {
            return 0;
        }

        // NROM-128(16KB) requires mirroring in 0xC000-0xFFFF range.
        auto local_address = static_cast<size_t>(target_address) % rom_size;
        return rom_data->data()[local_address];
    }

    // "Read Only"
    void primitive_rom::write(address target_address, uint8_t data) {};

    void primitive_rom::dump()
    {
        auto i = 0;
        uint32_t line_index = 0;
        auto byte_space_size = 1;
        auto block_space_size = 1;
        auto block_line_max = 4;

        auto calculate_line_offset = [&]() -> auto
        {
            return (line_index * 4 * block_line_max);
        };

        printf("[0x%04x] ", calculate_line_offset());
        for (const auto &e : *rom_data)
        {
            printf("%02x%*s", e, byte_space_size, "");
            i++;
            if (i % 4 == 0)
            {
                printf("%*s", block_space_size, "");
            }
            if (i % (4 * block_line_max) == 0)
            {
                i = 0;
                line_index++;
                printf("\n");
                printf("[0x%04x] ", calculate_line_offset());
            }
        }
        printf("\n");
    }

    rom::rom(const char *file_path)
    {
        auto rom_binary = open_rom_file(file_path);
        this->header = read_ines_header(rom_binary);
        ines_info();
        setup_rom(rom_binary);
    }

    std::ifstream rom::open_rom_file(const char *path)
    {
        std::ifstream file(path, std::ios::binary);
        return file;
    }

    ines_header rom::read_ines_header(std::ifstream &file)
    {
        ines_header header;
        file.read(reinterpret_cast<char *>(&header), sizeof(ines_header));
        return header;
    }

    void rom::ines_info()
    {
        uint8_t magic[5];
        std::memcpy(magic, this->header.nes, 4);
        magic[4] = '\0';

        auto program_rom_size = 16384 * this->header.program_rom_count;
        auto charactor_rom_size = 8192 * this->header.charactor_rom_count;

        printf("nes_magic\e[25G : %s\n", magic);
        printf("program_rom_size\e[25G : 0x%4x\n", program_rom_size);
        printf("charactor_rom_size\e[25G : 0x%4x\n", charactor_rom_size);

        printf("flag_6\e[25G :\n");
        printf("- mirroring\e[25G : %d\n", this->header.mirroring);
        printf(
            "- presisent_exists\e[25G : %d\n",
            this->header.persisent_memory_exists
        );
        printf("- trainer_exists\e[25G : %d\n", this->header.trainer_exists);
        printf(
            "- ignore_mirroring\e[25G : %d\n",
            this->header.ignore_mirroring
        );
        printf("- mapper_lower\e[25G : %d\n", this->header.mapper_lower);
        printf("\n");
    }

    void rom::setup_rom(std::ifstream &file)
    {
        auto program_rom_offset = sizeof(ines_header);
        program_rom_offset += this->header.trainer_exists ? 512 : 0;

        printf("program_rom_offset : 0x%04lx\n", program_rom_offset);

        auto program_rom_size = 16384 * this->header.program_rom_count;

        auto charactor_rom_offset = program_rom_offset + program_rom_size;
        auto charactor_rom_size = 8192 * this->header.charactor_rom_count;

        auto program_rom_data = create_vector_from_file(
            file,
            program_rom_offset,
            program_rom_size
        );

        auto charactor_rom_data = create_vector_from_file(
            file,
            charactor_rom_offset,
            charactor_rom_size
        );

        this->program
            = std::make_unique<primitive_rom>(std::move(program_rom_data));

        this->charactor
            = std::make_unique<primitive_rom>(std::move(charactor_rom_data));
    }

    void create_program_rom(std::ifstream &file)
    {
    }

    std::unique_ptr<std::vector<uint8_t>> rom::create_vector_from_file(
        std::ifstream &file,
        std::streamoff offset,
        size_t size
    )
    {
        auto data = std::make_unique<std::vector<uint8_t>>(size);

        file.seekg(offset, std::ios::beg);
        file.read(reinterpret_cast<char *>(data->data()), size);

        return data;
    }
}
