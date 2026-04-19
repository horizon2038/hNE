#include <standard/io/ppu/fltk_renderer.hpp>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include <array>
#include <cstdlib>

namespace hal::standard
{
    class fltk_ppu_view final : public Fl_Widget
    {
      public:
        fltk_ppu_view(
            int                                             x,
            int                                             y,
            int                                             w,
            int                                             h,
            std::array<uint8_t, fltk_ppu_renderer::SCREEN_WIDTH
                                  * fltk_ppu_renderer::SCREEN_HEIGHT * 3>
                &target_pixels
        )
            : Fl_Widget(x, y, w, h)
            , pixels(target_pixels)
        {
        }

        void draw() override
        {
            fl_draw_image(
                pixels.data(),
                x(),
                y(),
                fltk_ppu_renderer::SCREEN_WIDTH,
                fltk_ppu_renderer::SCREEN_HEIGHT,
                3
            );
        }

      private:
        std::array<uint8_t, fltk_ppu_renderer::SCREEN_WIDTH
                              * fltk_ppu_renderer::SCREEN_HEIGHT * 3>
            &pixels;
    };

    fltk_ppu_renderer::fltk_ppu_renderer()
    {
        for (size_t i = 0; i < pixels.size(); i++)
        {
            pixels[i] = 0;
        }

        const char *enable_window = std::getenv("HNE_PPU_WINDOW");
        if (enable_window != nullptr && enable_window[0] == '1')
        {
            window_enabled = true;
            window = std::make_unique<Fl_Window>(
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                "hNE PPU"
            );
            view = std::make_unique<fltk_ppu_view>(
                0,
                0,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                pixels
            );
            window->resizable(view.get());
            window->end();
            window->show();
        }
    }

    fltk_ppu_renderer::~fltk_ppu_renderer() = default;

    void fltk_ppu_renderer::on_vram_write(uint16_t ppu_address, uint8_t value)
    {
        auto pixel_index = static_cast<size_t>(ppu_address)
                         % static_cast<size_t>(SCREEN_WIDTH * SCREEN_HEIGHT);
        auto offset      = pixel_index * 3;
        auto color       = decode_color(value);

        pixels[offset + 0] = color[0];
        pixels[offset + 1] = color[1];
        pixels[offset + 2] = color[2];

        if (view)
        {
            view->redraw();
        }
    }

    void fltk_ppu_renderer::tick()
    {
        if (window_enabled)
        {
            Fl::check();
        }
    }

    std::array<uint8_t, 3> fltk_ppu_renderer::decode_color(uint8_t value) const
    {
        return {
            static_cast<uint8_t>((value & 0x03) * 85),
            static_cast<uint8_t>(((value >> 2) & 0x03) * 85),
            static_cast<uint8_t>(((value >> 4) & 0x03) * 85),
        };
    }
}
