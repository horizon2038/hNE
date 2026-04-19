#ifndef CORE_IO_PPU_PPU_HPP
#define CORE_IO_PPU_PPU_HPP

#include <core/io/io.hpp>
#include <core/io/ppu/renderer.hpp>

#include <array>
#include <chrono>
#include <cstdint>
#include <memory>

namespace core
{
    class ppu final : public io
    {
      public:
        explicit ppu(std::unique_ptr<ppu_renderer> init_renderer);
        ~ppu() override;

        uint8_t read(address target_address) override;
        void    write(address target_address, uint8_t data) override;

      private:
        static constexpr uint16_t VRAM_SIZE = 0x4000;
        static constexpr uint16_t OAM_SIZE  = 0x0100;

        std::array<uint8_t, VRAM_SIZE> vram {};
        std::array<uint8_t, OAM_SIZE>  oam {};
        std::unique_ptr<ppu_renderer>  renderer;

        uint8_t  ctrl {};
        uint8_t  mask {};
        uint8_t  status { 0x80 };
        uint8_t  oam_address {};
        uint8_t  fine_x {};
        uint16_t ppu_address {};
        uint8_t  read_buffer {};
        bool     write_toggle {};

        std::chrono::steady_clock::time_point last_vblank_tick;

        void process_gui();
        void update_vblank();

        uint8_t read_status();
        uint8_t read_oam_data();
        uint8_t read_data();

        void write_scroll(uint8_t data);
        void write_address(uint8_t data);
        void write_data(uint8_t data);

        uint16_t normalize_vram_address(uint16_t target_address) const;
        uint8_t  increment_step() const;
    };
}

#endif
