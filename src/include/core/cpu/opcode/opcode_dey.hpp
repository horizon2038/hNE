#ifndef CORE_OPCODE_DEY_HPP
#define CORE_OPCODE_DEY_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_dey final : public opcode
    {
      public:
        opcode_dey(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_dey() {};

        void execute() override
        {
            root_cpu.apply_cycles(2);
            auto target_value    = root_cpu.registers.y - 1;
            root_cpu.registers.y = target_value;

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
