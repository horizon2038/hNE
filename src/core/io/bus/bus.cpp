#include <core/io/bus/bus.hpp>

#include <stdio.h>
#include <utility>

namespace core
{
    bus::bus(
        std::unique_ptr<io> target_working_ram,
        std::unique_ptr<io> target_charactor_rom,
        std::unique_ptr<io> target_program_rom,
        std::unique_ptr<io> target_ppu
    )
        : working_ram(std::move(target_working_ram))
        , charactor_rom(std::move(target_charactor_rom))
        , program_rom(std::move(target_program_rom))
        , ppu(std::move(target_ppu))
    {
    }

    // nes memory_map
    //
    // +--------------------------------+
    // | address |   size |       about |
    // +--------------------------------+
    // |  0x0000 | 0x0800 |        wram |
    // +--------------------------------+
    // |  0x0800 | 0x0800 | wram_mirror |
    // +--------------------------------+
    // |  0x2000 | 0x0008 |         ppu |
    // +--------------------------------+
    // |  0x2008 | 0x0008 |  ppu_mirror |
    // +--------------------------------+
    // |  0x4000 | 0x0018 |    i/o regs |
    // +--------------------------------+
    // |  0x4018 | 0x0020 |   test mode |
    // +--------------------------------+
    // |  0x4020 | 0x1fe0 |     ext-rom |
    // +--------------------------------+
    // |  0x6000 | 0x2000 |     ext-ram |
    // +--------------------------------+
    // |  0x8000 | 0x4000 | program-rom |
    // +--------------------------------+
    // |  0xc000 | 0x4000 | program-rom |
    // +--------------------------------+

    io &bus::search_io_from_address(address target_address)
    {
        if (target_address < 0x0800)
        {
            // wram
            return *working_ram.get();
        }

        if (0x0800 <= target_address && target_address < 0x1000)
        {
            // mirror of wram
            return *working_ram.get();
        }

        if (0x2000 <= target_address && target_address < 0x2008)
        {
            // ppu registers
            return *ppu.get();
        }

        if (0x2008 <= target_address && target_address < 0x2010)
        {
            // mirror of ppu registers
            return *ppu.get();
        }

        if (0x4000 <= target_address && target_address < 0x4018)
        {
            // memory-mapped i/o (without apu)
        }

        if (0x4018 <= target_address && target_address < 0x4020)
        {
            // test mode
        }

        if (0x4020 <= target_address && target_address < 0x6000)
        {
            // extended rom
        }

        if (0x6000 <= target_address && target_address < 0x8000)
        {
            // extended ram
        }

        if (0x8000 <= target_address && target_address < 0xc000)
        {
            // program rom lower-half
            return *program_rom.get();
        }

        if (0xc000 <= target_address && target_address <= 0xFFFF)
        {
            // program rom higher-half
            return *program_rom.get();
        }

        // failed
        return empty_io;
    }

    address bus::convert_local_io_address(address target_address)
    {
        if (target_address < 0x0800)
        {
            // wram
            return target_address;
        }

        if (0x0800 <= target_address && target_address < 0x1000)
        {
            // mirror of wram
            return target_address - 0x0800;
        }

        if (0x2000 <= target_address && target_address < 0x2008)
        {
            // ppu registers
            return target_address - 0x2000;
        }

        if (0x2008 <= target_address && target_address < 0x2010)
        {
            // mirror of ppu registers
            return target_address - 0x2008;
        }

        if (0x4000 <= target_address && target_address < 0x4018)
        {
            // memory-mapped i/o (without apu)
            return target_address - 0x4000;
        }

        if (0x4018 <= target_address && target_address < 0x4020)
        {
            // test mode
            return target_address - 0x4018;
        }

        if (0x4020 <= target_address && target_address < 0x6000)
        {
            // extended rom
            return target_address - 0x4020;
        }

        if (0x6000 <= target_address && target_address < 0x8000)
        {
            // extended ram
        }

        if (0x8000 <= target_address && target_address < 0xc000)
        {
            // program rom lower-half
            return target_address - 0x8000;
        }

        if (0xc000 <= target_address && target_address <= 0xFFFF)
        {
            // program rom higher-half
            return target_address - 0x8000;
        }

        return 0;
    }

    void bus::write(address target_address, uint8_t data)
    {
        io     &target_io        = search_io_from_address(target_address);
        address local_io_address = convert_local_io_address(target_address);
        target_io.write(local_io_address, data);
    }

    uint8_t bus::read(address target_address)
    {
        io     &target_io        = search_io_from_address(target_address);
        address local_io_address = convert_local_io_address(target_address);
        /*
        printf(
            "read : [0x%04x 0x%04x] -> 0x%02x\n",
            target_address,
            local_io_address,
            target_io.read(local_io_address)
        );
        */
        return target_io.read(local_io_address);
    }

}
