#include <core/cpu/opcode/opcode_none.hpp>

#include <cstdio>

namespace core
{
    opcode_none::opcode_none(core::cpu &target_cpu) : _cpu(target_cpu)
    {
    }

    void opcode_none::execute()
    {
        _cpu.apply_cycles(1);
        std::printf("this opcode is not yet implemented\n");
    }
}
