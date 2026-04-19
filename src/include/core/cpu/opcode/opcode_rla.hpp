#ifndef CORE_OPCODE_RLA_HPP
#define CORE_OPCODE_RLA_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_rla final : public opcode
    {
      public:
        opcode_rla(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu }
        {
        }

        ~opcode_rla() override = default;

        void execute() override
        {
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

                case INDEXED_ABSOLUTE_Y :
                    root_cpu.apply_cycles(7);
                    break;

                case INDEXED_INDIRECT :
                    root_cpu.apply_cycles(8);
                    break;

                case INDIRECT_INDEXED :
                    root_cpu.apply_cycles(8);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            auto fetched_address = root_cpu.fetch_operand_address(mode);
            auto original_value  = root_cpu.bus->read(fetched_address);

            uint8_t old_carry
                = static_cast<uint8_t>(root_cpu.registers.carry ? 1 : 0);
            bool new_carry     = ((original_value & 0x80) != 0);

            auto rotated_value = static_cast<uint8_t>(
                ((original_value << 1) & 0xFF) | old_carry
            );

            root_cpu.registers.carry = new_carry;

            root_cpu.bus->write(fetched_address, rotated_value);

            auto final_value
                = static_cast<uint8_t>(root_cpu.registers.a & rotated_value);

            root_cpu.registers.a = final_value;
            root_cpu.update_zero(final_value);
            root_cpu.update_negative(final_value);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
