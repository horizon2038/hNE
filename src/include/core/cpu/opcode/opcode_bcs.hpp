#ifndef CORE_OPCODE_BCS_HPP
#define CORE_OPCODE_BCS_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_bcs final : public opcode
    {
      public:
        opcode_bcs(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_bcs() {};

        void execute() override
        {
            if (mode != addressing_mode::RELATIVE)
            {
                return;
            }

            auto target_address   = root_cpu.fetch_operand_address(mode);
            auto base_next_pc     = root_cpu.registers.pc;
            auto cycles           = static_cast<uint8_t>(2);

            if (root_cpu.registers.carry)
            {
                root_cpu.registers.pc = target_address;
                cycles = 3;

                if ((base_next_pc & 0xFF00) != (target_address & 0xFF00))
                {
                    cycles = 4;
                }
            }

            root_cpu.apply_cycles(cycles);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
