#ifndef STANDARD_IO_PPU_FLTK_RENDERER_HPP
#define STANDARD_IO_PPU_FLTK_RENDERER_HPP

#include <core/io/ppu/renderer.hpp>

#include <array>
#include <cstdint>
#include <memory>

class Fl_Window;

namespace hal::standard
{
    class fltk_ppu_view;

    class fltk_ppu_renderer final : public core::ppu_renderer
    {
      public:
        static constexpr int SCREEN_WIDTH  = 256;
        static constexpr int SCREEN_HEIGHT = 240;

        fltk_ppu_renderer();
        ~fltk_ppu_renderer() override;

        void on_vram_write(uint16_t ppu_address, uint8_t value) override;
        void tick() override;

      private:
        std::array<uint8_t, SCREEN_WIDTH * SCREEN_HEIGHT * 3> pixels {};
        std::unique_ptr<Fl_Window>    window;
        std::unique_ptr<fltk_ppu_view> view;
        bool                          window_enabled {};

        std::array<uint8_t, 3> decode_color(uint8_t value) const;
    };
}

#endif
