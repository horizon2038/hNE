#ifndef CORE_OPCODE_CLD_HPP
#define CORE_OPCODE_CLD_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_cld final : public opcode
    {
      public:
        opcode_cld(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_cld() {};

        void execute() override
        {
            root_cpu.registers.decimal_mode = false;
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
