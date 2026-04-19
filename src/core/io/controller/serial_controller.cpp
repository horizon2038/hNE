#include <core/io/controller/serial_controller.hpp>

namespace core
{
    uint8_t serial_controller::read(address target_address)
    {
        (void) target_address;

        if (strobe_enabled)
        {
            // While strobe is high, controller keeps presenting A button.
            return static_cast<uint8_t>(current_buttons & 0x01);
        }

        uint8_t value = static_cast<uint8_t>(shift_register & 0x01);
        shift_register = static_cast<uint8_t>((shift_register >> 1) | 0x80);

        return value;
    }

    void serial_controller::write(address target_address, uint8_t data)
    {
        (void) target_address;

        bool next_strobe = ((data & 0x01) != 0);

        // Latch on strobe high->low transition.
        if (strobe_enabled && !next_strobe)
        {
            shift_register = current_buttons;
        }

        strobe_enabled = next_strobe;
        if (strobe_enabled)
        {
            shift_register = current_buttons;
        }
    }

    void serial_controller::set_button_state(button target_button, bool pressed)
    {
        auto bit = button_to_bit(target_button);
        if (pressed)
        {
            current_buttons = static_cast<uint8_t>(current_buttons | bit);
        }
        else
        {
            current_buttons = static_cast<uint8_t>(current_buttons & ~bit);
        }

        if (strobe_enabled)
        {
            shift_register = current_buttons;
        }
    }

    uint8_t serial_controller::button_to_bit(button target_button)
    {
        return static_cast<uint8_t>(
            1u << static_cast<uint8_t>(target_button)
        );
    }
}
