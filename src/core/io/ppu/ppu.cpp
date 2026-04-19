#include <core/io/ppu/ppu.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>

namespace core
{
    namespace
    {
        constexpr uint16_t SCREEN_WIDTH      = 256;
        constexpr uint16_t SCREEN_HEIGHT     = 240;
        constexpr uint16_t NAMETABLE_BASE    = 0x2000;
        constexpr uint16_t NAMETABLE_END     = 0x3000;
        constexpr uint16_t NAMETABLE_SIZE    = 0x0400;
        constexpr uint16_t NAMETABLE_TILEMAP = 0x03C0;

        bool should_trace_ppu_mask()
        {
            static bool enabled = []()
            {
                const char *env = std::getenv("HNE_TRACE_PPU_MASK");
                return env != nullptr && env[0] == '1';
            }();
            return enabled;
        }

        bool should_trace_ppu_palette()
        {
            static bool enabled = []()
            {
                const char *env = std::getenv("HNE_TRACE_PPU_PALETTE");
                return env != nullptr && env[0] == '1';
            }();
            return enabled;
        }
    }

    ppu::ppu(std::unique_ptr<ppu_renderer> init_renderer, bool init_vertical_mirroring)
        : renderer(std::move(init_renderer))
        , vertical_mirroring(init_vertical_mirroring)
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
                ctrl             = data;
                temp_address     = static_cast<uint16_t>((temp_address & 0xF3FF) | ((data & 0x03) << 10));
                background_dirty = true;
                break;
            case 0x1 :
                mask             = data;
                background_dirty = true;

                if (renderer)
                {
                    renderer->set_mask(mask);
                }

                if (should_trace_ppu_mask())
                {
                    std::cout << std::format("PPUMASK <= 0x{:02X}", mask) << std::endl;
                }
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

    void ppu::tick()
    {
        process_gui();
    }

    bool ppu::poll_nmi()
    {
        if (!nmi_pending)
        {
            return false;
        }

        nmi_pending = false;
        return true;
    }

    void ppu::load_chr_rom(const std::vector<uint8_t> &data)
    {
        auto copy_size = std::min<size_t>(data.size(), 0x2000);
        for (size_t i = 0; i < copy_size; i++)
        {
            vram[i] = data[i];
        }
        background_dirty = true;
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
        // Approximate NTSC timing by CPU cycles.
        // 1 frame = 341 * 262 PPU cycles = 89342 PPU cycles ~= 29780 CPU
        // cycles. VBlank starts at scanline 241.
        constexpr uint32_t CPU_CYCLES_PER_FRAME   = 29780;
        constexpr uint32_t VBLANK_START_CPU_CYCLE = (241u * 341u) / 3u; // ~=27393
        // constexpr uint32_t RENDER_DELAY_IN_VBLANK = 800;

        cpu_cycles_in_frame++;

        if (cpu_cycles_in_frame == VBLANK_START_CPU_CYCLE)
        {
            status |= 0x80;

            if (ctrl & 0x80)
            {
                nmi_pending = true;
            }
        }

        if (cpu_cycles_in_frame >= CPU_CYCLES_PER_FRAME)
        {
            if (background_dirty)
            {
                render_background();
                background_dirty = false;
            }

            cpu_cycles_in_frame  = 0;
            status              &= static_cast<uint8_t>(~0x80);
            frame_rendered       = false;
        }

        /*
        if (!frame_rendered && background_dirty
            && cpu_cycles_in_frame >= (CPU_CYCLES_PER_FRAME - 1))
        {
            render_background();
            background_dirty = false;
            frame_rendered   = true;
        }
        */
    }

    uint8_t ppu::read_status()
    {
        update_vblank();

        uint8_t current_status  = status;
        status                 &= 0x7F;
        write_toggle            = false;

        return current_status;
    }

    uint8_t ppu::read_oam_data()
    {
        return oam[oam_address];
    }

    uint8_t ppu::read_data()
    {
        auto    normalized_address = normalize_vram_address(vram_address);
        auto    fetched_data       = vram[normalized_address];
        uint8_t return_data {};

        if (normalized_address >= 0x3F00)
        {
            return_data = fetched_data;
            read_buffer = vram[normalize_vram_address(normalized_address - 0x1000)];
        }
        else
        {
            return_data = read_buffer;
            read_buffer = fetched_data;
        }

        vram_address = normalize_vram_address(static_cast<uint16_t>(vram_address + increment_step()));
        return return_data;
    }

    void ppu::write_scroll(uint8_t data)
    {
        if (!write_toggle)
        {
            // First write to PPUSCROLL is horizontal scroll.
            coarse_x_scroll = static_cast<uint8_t>(data >> 3);
            fine_x_scroll   = data;
        }
        else
        {
            // Second write to PPUSCROLL is vertical scroll.
            scroll_y         = data;
            background_dirty = true;
        }

        write_toggle = !write_toggle;
    }

    void ppu::write_address(uint8_t data)
    {
        if (!write_toggle)
        {
            temp_address = static_cast<uint16_t>((temp_address & 0x00FF) | (static_cast<uint16_t>(data & 0x3F) << 8));

            std::cout << std::format("PPUADDR high <= 0x{:02X}, temp_address=0x{:04X}", data, temp_address) << std::endl;
        }
        else
        {
            temp_address = static_cast<uint16_t>((temp_address & 0xFF00) | static_cast<uint16_t>(data));
            vram_address = normalize_vram_address(temp_address);

            std::cout << std::format(
                "PPUADDR low  <= 0x{:02X}, temp_address=0x{:04X}, "
                "vram_address=0x{:04X}",
                data,
                temp_address,
                vram_address
            ) << std::endl;
        }

        write_toggle = !write_toggle;
    }

    void ppu::write_data(uint8_t data)
    {
        auto normalized_address  = normalize_vram_address(vram_address);
        vram[normalized_address] = data;

        if (should_trace_ppu_palette() && normalized_address >= 0x3F00 && normalized_address < 0x3F20)
        {
            std::cout << std::format("PPU PALETTE [0x{:04X}] <= 0x{:02X}", normalized_address, data) << std::endl;
        }

        if (normalized_address < 0x4000)
        {
            background_dirty = true;
        }

        if (normalized_address >= 0x2000 && normalized_address < 0x3000)
        {
            std::cout << std::format("NAMETABLE WRITE [0x{:04X}] <= 0x{:02X}", normalized_address, data) << std::endl;
        }

        if (normalized_address >= 0x3F00 && normalized_address < 0x3F20)
        {
            std::cout << std::format("PALETTE WRITE [0x{:04X}] <= 0x{:02X}", normalized_address, data) << std::endl;
        }

        vram_address = normalize_vram_address(static_cast<uint16_t>(vram_address + increment_step()));
    }

    void ppu::render_background()
    {
        if (!renderer)
        {
            return;
        }

        auto scroll_x       = static_cast<uint16_t>(fine_x_scroll) * 8 + static_cast<uint16_t>(coarse_x_scroll);
        auto scroll_y_value = static_cast<uint16_t>(scroll_y);
        auto base_nt        = static_cast<uint16_t>(ctrl & 0x0003);
        auto base_nt_x      = static_cast<uint16_t>(base_nt & 0x01);
        auto base_nt_y      = static_cast<uint16_t>((base_nt >> 1) & 0x01);

        auto pattern_base   = static_cast<uint16_t>((ctrl & 0x10) ? 0x1000 : 0x0000);

        for (uint16_t screen_y = 0; screen_y < SCREEN_HEIGHT; screen_y++)
        {
            auto world_y        = static_cast<uint16_t>(scroll_y_value + screen_y);
            auto tile_y_world   = static_cast<uint16_t>(world_y / 8);
            auto tile_y_local   = static_cast<uint8_t>(tile_y_world % 30);
            auto tile_row_pixel = static_cast<uint16_t>(world_y & 0x0007);
            auto nt_y_offset    = static_cast<uint16_t>((tile_y_world / 30) & 0x01);

            for (uint16_t screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++)
            {
                auto world_x             = static_cast<uint16_t>(scroll_x + screen_x);
                auto tile_x_world        = static_cast<uint16_t>(world_x / 8);
                auto tile_x_local        = static_cast<uint8_t>(tile_x_world % 32);
                auto tile_col_pixel      = static_cast<uint16_t>(world_x & 0x0007);
                auto nt_x_offset         = static_cast<uint16_t>((tile_x_world / 32) & 0x01);

                auto nametable_x         = static_cast<uint16_t>((base_nt_x + nt_x_offset) & 0x01);
                auto nametable_y         = static_cast<uint16_t>((base_nt_y + nt_y_offset) & 0x01);
                auto nametable_index     = static_cast<uint16_t>((nametable_y << 1) | nametable_x);
                auto nametable_base      = static_cast<uint16_t>(NAMETABLE_BASE + nametable_index * NAMETABLE_SIZE);

                auto tile_address        = static_cast<uint16_t>(nametable_base + tile_y_local * 32 + tile_x_local);
                auto tile_index          = read_vram(tile_address);

                auto pattern_row_address = static_cast<uint16_t>(pattern_base + tile_index * 16 + tile_row_pixel);
                auto low_plane           = read_vram(pattern_row_address);
                auto high_plane          = read_vram(static_cast<uint16_t>(pattern_row_address + 8));

                auto bit_index           = static_cast<uint8_t>(7 - tile_col_pixel);
                auto pixel_color_index
                    = static_cast<uint8_t>(((low_plane >> bit_index) & 0x01) | (((high_plane >> bit_index) & 0x01) << 1));

                auto palette_select = read_attribute_palette_select(nametable_base, tile_x_local, tile_y_local);
                auto palette_value  = read_background_palette_entry(palette_select, pixel_color_index);

                auto pixel_index    = static_cast<uint16_t>(screen_y * SCREEN_WIDTH + screen_x);
                renderer->on_vram_write(pixel_index, palette_value);

                if (screen_y == 109 && screen_x >= 20 && screen_x <= 24)
                {
                    std::cout << std::format(
                        "x={} y={} tile={} pattern_base=0x{:04X} "
                        "row_addr=0x{:04X} low=0x{:02X} high=0x{:02X} bit={} "
                        "pixel_idx={}",
                        screen_x,
                        screen_y,
                        tile_index,
                        pattern_base,
                        pattern_row_address,
                        low_plane,
                        high_plane,
                        bit_index,
                        pixel_color_index
                    ) << std::endl;
                }
            }
        }
    }

    uint8_t ppu::read_attribute_palette_select(uint16_t nametable_base, uint8_t tile_x, uint8_t tile_y) const
    {
        auto attribute_address = static_cast<uint16_t>(
            nametable_base + NAMETABLE_TILEMAP + static_cast<uint16_t>((tile_y / 4) * 8 + (tile_x / 4))
        );
        auto attribute_byte = read_vram(attribute_address);

        auto quadrant_x     = static_cast<uint8_t>((tile_x % 4) / 2);
        auto quadrant_y     = static_cast<uint8_t>((tile_y % 4) / 2);
        auto shift          = static_cast<uint8_t>((quadrant_y * 2 + quadrant_x) * 2);

        return static_cast<uint8_t>((attribute_byte >> shift) & 0x03);
    }

    uint8_t ppu::read_background_palette_entry(uint8_t palette_select, uint8_t pixel_color_index) const
    {
        if ((pixel_color_index & 0x03) == 0)
        {
            return read_vram(0x3F00);
        }

        auto palette_address = static_cast<uint16_t>(0x3F00 + (palette_select & 0x03) * 4 + (pixel_color_index & 0x03));
        return read_vram(palette_address);
    }

    uint8_t ppu::read_vram(uint16_t target_address) const
    {
        return vram[normalize_vram_address(target_address)];
    }

    uint16_t ppu::normalize_vram_address(uint16_t target_address) const
    {
        auto mirrored_address = static_cast<uint16_t>(target_address % VRAM_SIZE);

        // 0x3000-0x3EFF is a mirror of 0x2000-0x2EFF.
        if (mirrored_address >= 0x3000 && mirrored_address < 0x3F00)
        {
            mirrored_address = static_cast<uint16_t>(mirrored_address - 0x1000);
        }

        // 0x2000-0x2FFF nametables are mirrored into 2KB CIRAM.
        if (mirrored_address >= NAMETABLE_BASE && mirrored_address < NAMETABLE_END)
        {
            auto nametable_offset = static_cast<uint16_t>(mirrored_address - NAMETABLE_BASE);
            auto table_index      = static_cast<uint16_t>(nametable_offset / NAMETABLE_SIZE);
            auto in_table_offset  = static_cast<uint16_t>(nametable_offset % NAMETABLE_SIZE);

            uint16_t physical_table {};
            if (vertical_mirroring)
            {
                physical_table = static_cast<uint16_t>(table_index & 0x01);
            }
            else
            {
                physical_table = static_cast<uint16_t>((table_index >> 1) & 0x01);
            }

            return static_cast<uint16_t>(NAMETABLE_BASE + physical_table * NAMETABLE_SIZE + in_table_offset);
        }

        // Palette space mirrors every 0x20 bytes and has fixed mirrors.
        if (mirrored_address >= 0x3F00 && mirrored_address < 0x4000)
        {
            auto palette_address = static_cast<uint16_t>(0x3F00 + ((mirrored_address - 0x3F00) % 0x20));

            if (palette_address == 0x3F10 || palette_address == 0x3F14 || palette_address == 0x3F18
                || palette_address == 0x3F1C)
            {
                palette_address = static_cast<uint16_t>(palette_address - 0x10);
            }

            return palette_address;
        }

        return mirrored_address;
    }

    uint8_t ppu::increment_step() const
    {
        return (ctrl & 0x04) ? 32 : 1;
    }
}
