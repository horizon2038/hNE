#ifndef CORE_OPCODE_LAX_HPP
#define CORE_OPCODE_LAX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_lax final : public opcode
    {
      public:
        opcode_lax(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu }
        {
        }

        ~opcode_lax() override = default;

        void execute() override
        {
            using enum addressing_mode;

            switch (mode)
            {
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

                case INDEXED_INDIRECT :
                    root_cpu.apply_cycles(6);
                    break;

                case INDIRECT_INDEXED :
                    root_cpu.apply_cycles(5);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            auto    fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t target_value    = root_cpu.bus->read(fetched_address);

            root_cpu.registers.a    = target_value;
            root_cpu.registers.x    = target_value;

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
