#ifndef CORE_OPCODE_LDX_HPP
#define CORE_OPCODE_LDX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_ldx final : public opcode
    {
      public:
        opcode_ldx(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_ldx() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode, true);
            uint8_t target_value {};

            using enum addressing_mode;
            switch (mode)
            {
                case IMMEDIATE :
                    root_cpu.apply_cycles(2);
                    target_value         = fetched_address & 0xFF;
                    root_cpu.registers.x = target_value;
                    root_cpu.update_negative(target_value);
                    root_cpu.update_zero(target_value);
                    return;

                case ZERO_PAGE :
                    root_cpu.apply_cycles(3);
                    break;

                case INDEXED_ZERO_PAGE_Y :
                    root_cpu.apply_cycles(4);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(4);
                    break;

                case INDEXED_ABSOLUTE_Y :
                    root_cpu.apply_cycles(4);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            target_value         = root_cpu.bus->read(fetched_address);
            root_cpu.registers.x = target_value;

            // flag
            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
