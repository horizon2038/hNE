#include <core/cpu/opcode/opcode_jmp.hpp>

namespace core
{
    opcode_jmp::opcode_jmp(addressing_mode init_addressing_mode, cpu &target_cpu)
        : mode { init_addressing_mode }
        , root_cpu { target_cpu }
    {
    }

    void opcode_jmp::execute()
    {
        auto target_address   = root_cpu.fetch_operand_address(mode);
        root_cpu.registers.pc = target_address;

        using enum addressing_mode;
        switch (mode)
        {
            case ABSOLUTE :
                root_cpu.apply_cycles(3);
                break;

            case INDIRECT :
                root_cpu.apply_cycles(5);
                break;

            default :
                return;
        }
    }
}
