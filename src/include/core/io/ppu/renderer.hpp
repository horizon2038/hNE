#ifndef CORE_IO_PPU_RENDERER_HPP
#define CORE_IO_PPU_RENDERER_HPP

#include <cstdint>

namespace core
{
    class ppu_renderer
    {
      public:
        virtual ~ppu_renderer() {};

        virtual void on_vram_write(uint16_t ppu_address, uint8_t value) = 0;
        virtual void tick()                                              = 0;
    };
}

#endif
