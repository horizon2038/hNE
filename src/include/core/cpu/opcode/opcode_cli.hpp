#ifndef CORE_OPCODE_CLI_HPP
#define CORE_OPCODE_CLI_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_cli final : public opcode
    {
      public:
        opcode_cli(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_cli() {};

        void execute() override
        {
            root_cpu.registers.disable_irq = false;
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
