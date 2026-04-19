#ifndef CORE_OPCODE_PLA_HPP
#define CORE_OPCODE_PLA_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_pla final : public opcode
    {
      public:
        opcode_pla(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_pla() {};

        void execute() override
        {
            root_cpu.registers.a = root_cpu.pop();
            root_cpu.update_negative(root_cpu.registers.a);
            root_cpu.update_zero(root_cpu.registers.a);
            root_cpu.apply_cycles(4);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
