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
        auto value          = root_cpu.bus->read(target_address);

        using enum addressing_mode;
        switch (mode)
        {
            case ZERO_PAGE :
                root_cpu.apply_cycles(5);
                break;

            case INDEXED_ZERO_PAGE_X :
                root_cpu.apply_cycles(6);
                break;

            case ABSOLUTE :
                root_cpu.apply_cycles(6);
                break;

            case INDEXED_ABSOLUTE_X :
                root_cpu.apply_cycles(7);
                break;

            default :
                return;
        }

        value++;
        root_cpu.bus->write(target_address, value);
        root_cpu.update_zero(value);
        root_cpu.update_negative(value);
    }
}
