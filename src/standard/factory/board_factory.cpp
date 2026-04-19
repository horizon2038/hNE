#include <standard/factory/board_factory.hpp>

#include <core/cpu/opcode/init_opcodes.hpp>
#include <core/io/bus/bus.hpp>
#include <core/io/memory/ram.hpp>
#include <core/io/memory/rom.hpp>
#include <core/io/ppu/ppu.hpp>
#include <standard/board/board.hpp>
#include <standard/io/controller/fltk_key_controller.hpp>
#include <standard/io/ppu/fltk_renderer.hpp>

namespace hal::standard
{
    std::unique_ptr<core::board> board_factory::make(const char *rom_path)
    {
        auto ram      = std::make_unique<core::working_ram>();
        auto rom      = std::make_unique<core::rom>(rom_path);
        auto controller1 = std::make_unique<fltk_key_controller>();
        auto renderer = std::make_unique<fltk_ppu_renderer>(controller1.get());
        auto ppu      = std::make_unique<core::ppu>(
            std::move(renderer),
            rom->header.mirroring != 0
        );

        if (auto *chr_rom = dynamic_cast<core::primitive_rom *>(rom->charactor.get()))
        {
            ppu->load_chr_rom(chr_rom->raw_data());
        }

        auto bus      = std::make_unique<core::bus>(
            std::move(ram),
            std::move(rom->charactor),
            std::move(rom->program),
            std::move(ppu),
            std::move(controller1)
        );

        auto cpu = std::make_unique<core::cpu>(std::move(bus));
        init_opcodes(*cpu);

        return std::make_unique<hal::standard::board>(std::move(cpu));
    }
}
