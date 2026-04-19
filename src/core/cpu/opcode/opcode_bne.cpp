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
        if (!root_cpu.registers.zero)
        {
            auto target_address = root_cpu.fetch_operand_address(mode);
            root_cpu.registers.pc = target_address;
            root_cpu.apply_cycles(1); // +1 cycle if branch succeeds
        }
        root_cpu.apply_cycles(2); // base cycles
    }
}
