#ifndef CORE_OPCODE_SED_HPP
#define CORE_OPCODE_SED_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_sed final : public opcode
    {
      public:
        opcode_sed(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_sed() {};

        void execute() override
        {
            root_cpu.registers.decimal_mode = true;
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
