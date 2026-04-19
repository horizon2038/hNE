#ifndef CORE_IO_PPU_PPU_HPP
#define CORE_IO_PPU_PPU_HPP

#include <core/io/io.hpp>
#include <core/io/ppu/renderer.hpp>

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

namespace core
{
    class ppu final : public io
    {
      public:
        explicit ppu(
            std::unique_ptr<ppu_renderer> init_renderer,
            bool                          init_vertical_mirroring
        );
        ~ppu() override;

        uint8_t read(address target_address) override;
        void    write(address target_address, uint8_t data) override;
        void    tick() override;
        bool    poll_nmi() override;
        void    load_chr_rom(const std::vector<uint8_t> &data);

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
        uint8_t  coarse_x_scroll {};
        uint8_t  fine_x_scroll {};
        uint8_t  scroll_y {};
        uint16_t vram_address {};
        uint16_t temp_address {};
        uint8_t  read_buffer {};
        bool     write_toggle {};
        bool     nmi_pending {};
        bool     vertical_mirroring {};
        bool     background_dirty { true };
        bool     frame_rendered {};
        uint32_t cpu_cycles_in_frame {};

        void process_gui();
        void update_vblank();

        uint8_t read_status();
        uint8_t read_oam_data();
        uint8_t read_data();

        void write_scroll(uint8_t data);
        void write_address(uint8_t data);
        void write_data(uint8_t data);

        void    render_background();
        uint8_t read_attribute_palette_select(
            uint16_t nametable_base,
            uint8_t  tile_x,
            uint8_t  tile_y
        ) const;
        uint8_t read_background_palette_entry(
            uint8_t palette_select,
            uint8_t pixel_color_index
        ) const;
        uint8_t read_vram(uint16_t target_address) const;

        uint16_t normalize_vram_address(uint16_t target_address) const;
        uint8_t  increment_step() const;
    };
}

#endif
