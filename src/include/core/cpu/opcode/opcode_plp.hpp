#ifndef CORE_OPCODE_PLP_HPP
#define CORE_OPCODE_PLP_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_plp final : public opcode
    {
      public:
        opcode_plp(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_plp() {};

        void execute() override
        {
            root_cpu.registers.p        = root_cpu.pop();
            root_cpu.registers.reserved = true;
            root_cpu.apply_cycles(4);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
