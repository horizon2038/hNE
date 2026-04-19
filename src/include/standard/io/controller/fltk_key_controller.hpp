#ifndef STANDARD_IO_CONTROLLER_FLTK_KEY_CONTROLLER_HPP
#define STANDARD_IO_CONTROLLER_FLTK_KEY_CONTROLLER_HPP

#include <core/io/controller/key_input_sink.hpp>
#include <core/io/controller/serial_controller.hpp>

namespace hal::standard
{
    class fltk_key_controller final : public core::serial_controller,
                                      public core::key_input_sink
    {
      public:
        fltk_key_controller()          = default;
        ~fltk_key_controller() override = default;

        void on_key_event(int key, bool pressed) override;
    };
}

#endif
