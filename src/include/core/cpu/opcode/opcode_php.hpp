#ifndef CORE_OPCODE_PHP_HPP
#define CORE_OPCODE_PHP_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_php final : public opcode
    {
      public:
        opcode_php(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_php() {};

        void execute() override
        {
            auto previous_break    = root_cpu.registers.break_mode;
            auto previous_reserved = root_cpu.registers.reserved;

            root_cpu.registers.break_mode = true;
            root_cpu.registers.reserved   = true;
            root_cpu.push(root_cpu.registers.p);

            root_cpu.registers.break_mode = previous_break;
            root_cpu.registers.reserved   = previous_reserved;
            root_cpu.apply_cycles(3);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
