#ifndef CORE_OPCODE_PHA_HPP
#define CORE_OPCODE_PHA_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_pha final : public opcode
    {
      public:
        opcode_pha(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_pha() {};

        void execute() override
        {
            root_cpu.push(root_cpu.registers.a);
            root_cpu.apply_cycles(3);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
