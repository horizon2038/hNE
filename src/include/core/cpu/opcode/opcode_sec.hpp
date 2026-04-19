#ifndef CORE_OPCODE_SEC_HPP
#define CORE_OPCODE_SEC_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_sec final : public opcode
    {
      public:
        opcode_sec(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_sec() {};

        void execute() override
        {
            root_cpu.registers.carry = true;
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
