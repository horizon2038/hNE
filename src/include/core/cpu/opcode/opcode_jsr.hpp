#ifndef CORE_OPCODE_JSR_HPP
#define CORE_OPCODE_JSR_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_jsr final : public opcode
    {
      public:
        opcode_jsr(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_jsr() {};

        void execute() override
        {
            if (mode != addressing_mode::ABSOLUTE)
            {
                return;
            }

            auto target_address = root_cpu.fetch_operand_address(mode);
            auto return_address = static_cast<uint16_t>(root_cpu.registers.pc - 1);

            root_cpu.push(static_cast<uint8_t>((return_address >> 8) & 0xFF));
            root_cpu.push(static_cast<uint8_t>(return_address & 0xFF));

            root_cpu.registers.pc = target_address;
            root_cpu.apply_cycles(6);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
