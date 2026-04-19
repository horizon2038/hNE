#include <core/io/bus/bus.hpp>

#include <stdio.h>
#include <utility>

namespace core
{
    bus::bus(
        std::unique_ptr<io> target_working_ram,
        std::unique_ptr<io> target_charactor_rom,
        std::unique_ptr<io> target_program_rom,
        std::unique_ptr<io> target_ppu,
        std::unique_ptr<io> target_controller1
    )
        : working_ram(std::move(target_working_ram))
        , charactor_rom(std::move(target_charactor_rom))
        , program_rom(std::move(target_program_rom))
        , ppu(std::move(target_ppu))
        , controller1(std::move(target_controller1))
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
        if (target_address < 0x2000)
        {
            // wram and mirrors (0x0000-0x1FFF)
            return *working_ram.get();
        }

        if (0x2000 <= target_address && target_address < 0x4000)
        {
            // ppu registers and mirrors (0x2000-0x3FFF)
            return *ppu.get();
        }

        if (0x4000 <= target_address && target_address < 0x4018)
        {
            if (target_address == 0x4016 && controller1)
            {
                // controller port 1
                return *controller1.get();
            }
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
        if (target_address < 0x2000)
        {
            // wram and mirrors (2KB mirrored in 0x0000-0x1FFF)
            return target_address & 0x07FF;
        }

        if (0x2000 <= target_address && target_address < 0x4000)
        {
            // ppu regs mirrored every 8 bytes
            return target_address & 0x0007;
        }

        if (0x4000 <= target_address && target_address < 0x4018)
        {
            if (target_address == 0x4016)
            {
                return 0x0000;
            }
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

    void bus::tick()
    {
        if (ppu)
        {
            ppu->tick();
        }
    }

    bool bus::poll_nmi()
    {
        if (!ppu)
        {
            return false;
        }
        return ppu->poll_nmi();
    }

    void bus::write(address target_address, uint8_t data)
    {
        // OAM DMA: copy 256 bytes from CPU page $XX00-$XXFF to PPU OAMDATA.
        if (target_address == 0x4014 && ppu)
        {
            auto dma_base = static_cast<address>(data) << 8;
            for (address offset = 0; offset < 0x0100; offset++)
            {
                auto value = read(static_cast<address>(dma_base + offset));
                ppu->write(0x0004, value);
            }
            return;
        }

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
