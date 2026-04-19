#ifndef CORE_OPCODE_DEX_HPP
#define CORE_OPCODE_DEX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_dex final : public opcode
    {
      public:
        opcode_dex(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_dex() {};

        void execute() override
        {
            root_cpu.apply_cycles(2);
            auto target_value    = root_cpu.registers.x - 1;
            root_cpu.registers.x = target_value;

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
