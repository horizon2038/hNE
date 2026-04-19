#include <core/cpu/opcode/opcode_bne.hpp>

namespace core
{
    opcode_bne::opcode_bne(addressing_mode init_addressing_mode, cpu &target_cpu)
        : mode { init_addressing_mode }
        , root_cpu { target_cpu }
    {
    }

    void opcode_bne::execute()
    {
        if (mode != addressing_mode::RELATIVE)
        {
            return;
        }

        auto target_address = root_cpu.fetch_operand_address(mode);
        auto base_next_pc   = root_cpu.registers.pc;
        auto cycles         = static_cast<uint8_t>(2);

        if (!root_cpu.registers.zero)
        {
            root_cpu.registers.pc = target_address;

            cycles                = 3;
            if ((base_next_pc & 0xFF00) != (target_address & 0xFF00))
            {
                cycles = 4;
            }
        }

        root_cpu.apply_cycles(cycles);
    }
}
