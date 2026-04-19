#ifndef CORE_IO_CONTROLLER_SERIAL_CONTROLLER_HPP
#define CORE_IO_CONTROLLER_SERIAL_CONTROLLER_HPP

#include <core/io/controller/controller.hpp>

#include <cstdint>

namespace core
{
    class serial_controller : public controller
    {
      public:
        serial_controller()           = default;
        ~serial_controller() override = default;

        uint8_t read(address target_address) override;
        void    write(address target_address, uint8_t data) override;
        void    set_button_state(button target_button, bool pressed) override;

      protected:
        uint8_t current_buttons {};
        uint8_t shift_register {};
        bool    strobe_enabled {};

      private:
        static uint8_t button_to_bit(button target_button);
    };
}

#endif
