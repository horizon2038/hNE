#include <standard/io/controller/fltk_key_controller.hpp>

#include <FL/Enumerations.H>

namespace hal::standard
{
    void fltk_key_controller::on_key_event(int key, bool pressed)
    {
        switch (key)
        {
            case FL_Up :
                set_button_state(core::controller::button::UP, pressed);
                break;
            case FL_Down :
                set_button_state(core::controller::button::DOWN, pressed);
                break;
            case FL_Left :
                set_button_state(core::controller::button::LEFT, pressed);
                break;
            case FL_Right :
                set_button_state(core::controller::button::RIGHT, pressed);
                break;
            case 'z' :
            case 'Z' :
                set_button_state(core::controller::button::START, pressed);
                break;
            case 'x' :
            case 'X' :
                set_button_state(core::controller::button::SELECT, pressed);
                break;
            case 'a' :
            case 'A' :
                set_button_state(core::controller::button::A, pressed);
                break;
            case 's' :
            case 'S' :
                set_button_state(core::controller::button::B, pressed);
                break;

            default :
                break;
        }
    }
}
