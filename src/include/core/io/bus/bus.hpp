#ifndef BUS_HPP
#define BUS_HPP

#include <core/io/io.hpp>
#include <core/common/common.hpp>
#include <core/io/io_stab.hpp>

#include <stdint.h>
#include <memory>

namespace core
{
    class bus final : public io
    {
      public:
        bus(std::unique_ptr<io> target_working_ram,
            std::unique_ptr<io> target_charactor_rom,
            std::unique_ptr<io> target_program_rom,
            std::unique_ptr<io> target_ppu,
            std::unique_ptr<io> target_controller1);

        void write(address target_address, uint8_t data) override;
        uint8_t read(address target_address) override;
        void tick() override;
        bool poll_nmi() override;

      private:
        std::unique_ptr<io> working_ram;
        std::unique_ptr<io> charactor_rom;
        std::unique_ptr<io> program_rom;
        std::unique_ptr<io> ppu;
        std::unique_ptr<io> controller1;

        io_stab empty_io;

        io &search_io_from_address(address target_address);
        address convert_local_io_address(address target_address);
    };
}

#endif
