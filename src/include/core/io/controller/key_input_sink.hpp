#ifndef CORE_IO_CONTROLLER_KEY_INPUT_SINK_HPP
#define CORE_IO_CONTROLLER_KEY_INPUT_SINK_HPP

namespace core
{
    class key_input_sink
    {
      public:
        virtual ~key_input_sink()                        = default;

        virtual void on_key_event(int key, bool pressed) = 0;
    };
}

#endif
