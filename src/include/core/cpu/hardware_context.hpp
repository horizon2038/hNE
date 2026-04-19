#ifndef CORE_HARDWARE_CONTEXT_HPP
#define CORE_HARDWARE_CONTEXT_HPP

#include <stdint.h>

namespace core
{
    struct hardware_context
    {
        // accumlator
        uint8_t a;

        // index register
        uint8_t x;
        uint8_t y;

        // program counter
        uint16_t pc;

        // stack pointer
        // 0x0100 + stack pointer = wram address
        uint8_t s;

        // status register
        union
        {
            uint8_t p;

            // C Z I D B U V N (bit0 -> bit7)
            struct
            {
                uint8_t carry : 1;
                uint8_t zero : 1;
                uint8_t disable_irq : 1;
                uint8_t decimal_mode : 1;
                uint8_t break_mode : 1;
                uint8_t reserved : 1;
                uint8_t overflow : 1;
                uint8_t negative : 1;
            };
        };

        void init_registers()
        {
            pc = 0;

            a = 0;
            x = 0;
            y = 0;
            s = 0xFD;

            // After reset: IRQ disabled + reserved bit set.
            p = 0x24;
        }
    };
}
#endif
