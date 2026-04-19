#ifndef CORE_OPCODE_CLC_HPP
#define CORE_OPCODE_CLC_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_clc final : public opcode
    {
      public:
        opcode_clc(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_clc() {};

        void execute() override
        {
            root_cpu.registers.carry = false;
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
