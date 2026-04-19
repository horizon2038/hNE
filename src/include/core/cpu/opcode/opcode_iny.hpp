#ifndef CORE_OPCODE_INY_HPP
#define CORE_OPCODE_INY_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_iny final : public opcode
    {
      public:
        opcode_iny(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_iny() {};

        void execute() override
        {
            root_cpu.registers.y++;
            root_cpu.update_zero(root_cpu.registers.y);
            root_cpu.update_negative(root_cpu.registers.y);
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
