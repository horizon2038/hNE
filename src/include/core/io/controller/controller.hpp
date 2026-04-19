#ifndef CORE_IO_CONTROLLER_CONTROLLER_HPP
#define CORE_IO_CONTROLLER_CONTROLLER_HPP

#include <core/io/io.hpp>

#include <cstdint>

namespace core
{
    class controller : public io
    {
      public:
        enum class button : uint8_t
        {
            A      = 0,
            B      = 1,
            SELECT = 2,
            START  = 3,
            UP     = 4,
            DOWN   = 5,
            LEFT   = 6,
            RIGHT  = 7,
        };

        ~controller() override = default;

        virtual void set_button_state(button target_button, bool pressed) = 0;
    };
}

#endif
