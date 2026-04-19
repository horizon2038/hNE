#include <core/cpu/opcode/opcode_inc.hpp>

namespace core
{
    opcode_inc::opcode_inc(addressing_mode init_addressing_mode, cpu &target_cpu)
        : mode { init_addressing_mode }
        , root_cpu { target_cpu }
    {
    }

    void opcode_inc::execute()
    {
        auto target_address = root_cpu.fetch_operand_address(mode);
        auto value = root_cpu.bus->read(target_address);
        value++;
        root_cpu.bus->write(target_address, value);
        root_cpu.update_zero(value);
        root_cpu.update_negative(value);
        root_cpu.apply_cycles(5);
    }
}
