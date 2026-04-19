#include <core/io/ppu/ppu.hpp>

namespace core
{
    ppu::ppu(std::unique_ptr<ppu_renderer> init_renderer)
        : renderer(std::move(init_renderer))
        , last_vblank_tick(std::chrono::steady_clock::now())
    {
    }

    ppu::~ppu() = default;

    uint8_t ppu::read(address target_address)
    {
        process_gui();

        auto register_address = static_cast<uint8_t>(target_address & 0x7);
        switch (register_address)
        {
            case 0x2 :
                return read_status();
            case 0x4 :
                return read_oam_data();
            case 0x7 :
                return read_data();
            default :
                return 0;
        }
    }

    void ppu::write(address target_address, uint8_t data)
    {
        process_gui();

        auto register_address = static_cast<uint8_t>(target_address & 0x7);
        switch (register_address)
        {
            case 0x0 :
                ctrl = data;
                break;
            case 0x1 :
                mask = data;
                break;
            case 0x3 :
                oam_address = data;
                break;
            case 0x4 :
                oam[oam_address] = data;
                oam_address++;
                break;
            case 0x5 :
                write_scroll(data);
                break;
            case 0x6 :
                write_address(data);
                break;
            case 0x7 :
                write_data(data);
                break;
            default :
                break;
        }
    }

    void ppu::process_gui()
    {
        update_vblank();
        if (renderer)
        {
            renderer->tick();
        }
    }

    void ppu::update_vblank()
    {
        constexpr auto frame_time = std::chrono::milliseconds(16);
        auto           now        = std::chrono::steady_clock::now();

        if ((now - last_vblank_tick) >= frame_time)
        {
            status |= 0x80;
            last_vblank_tick = now;
        }
    }

    uint8_t ppu::read_status()
    {
        update_vblank();
        uint8_t current_status = status;
        status &= 0x7F;
        write_toggle = false;
        return current_status;
    }

    uint8_t ppu::read_oam_data()
    {
        return oam[oam_address];
    }

    uint8_t ppu::read_data()
    {
        auto normalized_address = normalize_vram_address(ppu_address);
        auto fetched_data       = vram[normalized_address];
        uint8_t return_data {};

        if (normalized_address >= 0x3F00)
        {
            return_data = fetched_data;
            read_buffer
                = vram[normalize_vram_address(normalized_address - 0x1000)];
        }
        else
        {
            return_data = read_buffer;
            read_buffer = fetched_data;
        }

        ppu_address = normalize_vram_address(
            static_cast<uint16_t>(ppu_address + increment_step())
        );
        return return_data;
    }

    void ppu::write_scroll(uint8_t data)
    {
        if (!write_toggle)
        {
            fine_x = data;
        }
        write_toggle = !write_toggle;
    }

    void ppu::write_address(uint8_t data)
    {
        if (!write_toggle)
        {
            ppu_address = static_cast<uint16_t>((data & 0x3F) << 8)
                        | static_cast<uint16_t>(ppu_address & 0x00FF);
        }
        else
        {
            ppu_address = static_cast<uint16_t>(ppu_address & 0xFF00)
                        | static_cast<uint16_t>(data);
            ppu_address = normalize_vram_address(ppu_address);
        }
        write_toggle = !write_toggle;
    }

    void ppu::write_data(uint8_t data)
    {
        auto normalized_address = normalize_vram_address(ppu_address);
        vram[normalized_address] = data;

        if (renderer)
        {
            renderer->on_vram_write(normalized_address, data);
        }

        ppu_address = normalize_vram_address(
            static_cast<uint16_t>(ppu_address + increment_step())
        );
    }

    uint16_t ppu::normalize_vram_address(uint16_t target_address) const
    {
        return static_cast<uint16_t>(target_address % VRAM_SIZE);
    }

    uint8_t ppu::increment_step() const
    {
        return (ctrl & 0x04) ? 32 : 1;
    }
}
