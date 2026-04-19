#include <standard/io/ppu/fltk_renderer.hpp>

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#include <array>
#include <chrono>
#include <cstdlib>

namespace hal::standard
{
    class fltk_ppu_view final : public Fl_Widget
    {
      public:
        fltk_ppu_view(
            int                                                                                          x,
            int                                                                                          y,
            int                                                                                          w,
            int                                                                                          h,
            std::array<uint8_t, fltk_ppu_renderer::SCREEN_WIDTH * fltk_ppu_renderer::SCREEN_HEIGHT * 3> &target_pixels,
            core::key_input_sink *init_key_input_sink
        )
            : Fl_Widget(x, y, w, h)
            , pixels(target_pixels)
            , key_input_sink(init_key_input_sink)
        {
        }

        void draw() override
        {
            fl_draw_image(pixels.data(), x(), y(), fltk_ppu_renderer::SCREEN_WIDTH, fltk_ppu_renderer::SCREEN_HEIGHT, 3);
        }

        int handle(int event) override
        {
            switch (event)
            {
                case FL_FOCUS :
                case FL_UNFOCUS :
                    return 1;

                case FL_KEYBOARD :
                case FL_SHORTCUT :
                case FL_KEYUP :
                    if (key_input_sink)
                    {
                        key_input_sink->on_key_event(Fl::event_key(), event == FL_KEYDOWN);
                    }
                    return 1;

                default :
                    break;
            }

            return Fl_Widget::handle(event);
        }

      private:
        std::array<uint8_t, fltk_ppu_renderer::SCREEN_WIDTH * fltk_ppu_renderer::SCREEN_HEIGHT * 3> &pixels;
        core::key_input_sink                                                                        *key_input_sink {};
    };

    fltk_ppu_renderer::fltk_ppu_renderer(core::key_input_sink *init_key_input_sink)
        : last_event_poll(std::chrono::steady_clock::now())
        , last_present(std::chrono::steady_clock::now())
        , key_input_sink(init_key_input_sink)
    {
        for (size_t i = 0; i < pixels.size(); i++)
        {
            pixels[i] = 0;
        }

        const char *enable_window = std::getenv("HNE_PPU_WINDOW");
        if (enable_window != nullptr && enable_window[0] == '1')
        {
            window_enabled = true;
            window         = std::make_unique<Fl_Window>(SCREEN_WIDTH, SCREEN_HEIGHT, "hNE PPU");
            window->color(FL_BLACK);
            view = std::make_unique<fltk_ppu_view>(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, pixels, key_input_sink);
            window->resizable(view.get());
            window->end();
            window->show();
            view->take_focus();
            dirty = true;
        }
    }

    fltk_ppu_renderer::~fltk_ppu_renderer() = default;

    void fltk_ppu_renderer::on_vram_write(uint16_t ppu_address, uint8_t value)
    {
        auto pixel_index   = static_cast<size_t>(ppu_address) % static_cast<size_t>(SCREEN_WIDTH * SCREEN_HEIGHT);
        auto offset        = pixel_index * 3;
        auto color         = decode_color(value);

        pixels[offset + 0] = color[0];
        pixels[offset + 1] = color[1];
        pixels[offset + 2] = color[2];
        dirty              = true;
    }

    void fltk_ppu_renderer::tick()
    {
        if (!window_enabled)
        {
            return;
        }

        using namespace std::chrono;
        auto now = steady_clock::now();

        // Pump FLTK events often enough for input/close handling.
        if ((now - last_event_poll) >= 1ms)
        {
            Fl::check();
            last_event_poll = now;
        }

        // Present at ~60fps max instead of redrawing on every CPU tick.
        if (dirty && (now - last_present) >= 16ms)
        {
            if (view)
            {
                view->redraw();
            }
            dirty        = false;
            last_present = now;
        }
    }

    std::array<uint8_t, 3> fltk_ppu_renderer::decode_color(uint8_t value) const
    {
        static constexpr std::array<std::array<uint8_t, 3>, 64> nes_palette = {
            std::array<uint8_t, 3> { 84, 84, 84 },
            { 0, 30, 116 },
            { 8, 16, 144 },
            { 48, 0, 136 },
            { 68, 0, 100 },
            { 92, 0, 48 },
            { 84, 4, 0 },
            { 60, 24, 0 },
            { 32, 42, 0 },
            { 8, 58, 0 },
            { 0, 64, 0 },
            { 0, 60, 0 },
            { 0, 50, 60 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 152, 150, 152 },
            { 8, 76, 196 },
            { 48, 50, 236 },
            { 92, 30, 228 },
            { 136, 20, 176 },
            { 160, 20, 100 },
            { 152, 34, 32 },
            { 120, 60, 0 },
            { 84, 90, 0 },
            { 40, 114, 0 },
            { 8, 124, 0 },
            { 0, 118, 40 },
            { 0, 102, 120 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 236, 238, 236 },
            { 76, 154, 236 },
            { 120, 124, 236 },
            { 176, 98, 236 },
            { 228, 84, 236 },
            { 236, 88, 180 },
            { 236, 106, 100 },
            { 212, 136, 32 },
            { 160, 170, 0 },
            { 116, 196, 0 },
            { 76, 208, 32 },
            { 56, 204, 108 },
            { 56, 180, 204 },
            { 60, 60, 60 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 236, 238, 236 },
            { 168, 204, 236 },
            { 188, 188, 236 },
            { 212, 178, 236 },
            { 236, 174, 236 },
            { 236, 174, 212 },
            { 236, 180, 176 },
            { 228, 196, 144 },
            { 204, 210, 120 },
            { 180, 222, 120 },
            { 168, 226, 144 },
            { 152, 226, 180 },
            { 160, 214, 228 },
            { 160, 162, 160 },
            { 0, 0, 0 },
            { 0, 0, 0 },
        };

        auto color_index = static_cast<uint8_t>(value & 0x3F);
        auto color       = nes_palette[color_index];

        // PPUMASK bit 0: grayscale
        if ((current_mask & 0x01) != 0)
        {
            auto luminance = static_cast<uint8_t>(
                (static_cast<uint16_t>(color[0]) * 30 + static_cast<uint16_t>(color[1]) * 59
                 + static_cast<uint16_t>(color[2]) * 11)
                / 100
            );

            color[0] = luminance;
            color[1] = luminance;
            color[2] = luminance;
        }

        // PPUMASK bit 5-7: color emphasis
        // bit5: emphasize red
        // bit6: emphasize green
        // bit7: emphasize blue
        auto apply_emphasis = [](uint8_t component, bool emphasized) -> uint8_t
        {
            uint16_t scaled
                = emphasized ? static_cast<uint16_t>(component) * 115 / 100 : static_cast<uint16_t>(component) * 85 / 100;

            if (scaled > 255)
            {
                scaled = 255;
            }

            return static_cast<uint8_t>(scaled);
        };

        bool emphasize_red   = (current_mask & 0x20) != 0;
        bool emphasize_green = (current_mask & 0x40) != 0;
        bool emphasize_blue  = (current_mask & 0x80) != 0;

        if (emphasize_red || emphasize_green || emphasize_blue)
        {
            color[0] = apply_emphasis(color[0], emphasize_red);
            color[1] = apply_emphasis(color[1], emphasize_green);
            color[2] = apply_emphasis(color[2], emphasize_blue);
        }

        return color;
    }

}
