#include <core/cpu/opcode/opcode_sei.hpp>

namespace core
{
    opcode_sei::opcode_sei(cpu &target_cpu) : root_cpu { target_cpu }
    {
    }

    void opcode_sei::execute()
    {
        root_cpu.registers.disable_irq = true;
        root_cpu.apply_cycles(2);
    }
}
