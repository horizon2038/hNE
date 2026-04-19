#include <core/cpu/opcode/opcode_inx.hpp>

namespace core
{
    opcode_inx::opcode_inx(cpu &target_cpu) : root_cpu { target_cpu }
    {
    }

    void opcode_inx::execute()
    {
        root_cpu.registers.x++;
        root_cpu.update_zero(root_cpu.registers.x);
        root_cpu.update_negative(root_cpu.registers.x);
        root_cpu.apply_cycles(2);
    }
}
