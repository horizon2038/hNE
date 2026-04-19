#ifndef CORE_OPCODE_RTI_HPP
#define CORE_OPCODE_RTI_HPP

#include <core/common/common.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_rti final : public opcode
    {
      public:
        opcode_rti(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_rti() {};

        void execute() override
        {
            root_cpu.registers.p        = root_cpu.pop();
            root_cpu.registers.reserved = true;

            auto lower_address          = root_cpu.pop();
            auto higher_address         = root_cpu.pop();
            root_cpu.registers.pc       = merge_address(lower_address, higher_address);
            root_cpu.apply_cycles(6);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
