#ifndef CORE_OPCODE_RRA_HPP
#define CORE_OPCODE_RRA_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_rra final : public opcode
    {
      public:
        opcode_rra(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu }
        {
        }

        ~opcode_rra() override = default;

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
            bool new_carry = ((original_value & 0x01) != 0);

            auto rotated_value
                = static_cast<uint8_t>((original_value >> 1) | (old_carry << 7));

            root_cpu.registers.carry = new_carry;

            root_cpu.bus->write(fetched_address, rotated_value);

            // --- ADC 部分 ---
            uint8_t accumulator = root_cpu.registers.a;

            uint16_t result     = static_cast<uint16_t>(accumulator)
                            + static_cast<uint16_t>(rotated_value)
                            + static_cast<uint16_t>(root_cpu.registers.carry);

            uint8_t final_result     = static_cast<uint8_t>(result & 0xFF);

            root_cpu.registers.carry = (result > 0xFF);

            root_cpu.registers.overflow
                = ((accumulator ^ final_result) & (rotated_value ^ final_result)
                   & 0x80)
               != 0;

            root_cpu.registers.a = final_result;
            root_cpu.update_zero(final_result);
            root_cpu.update_negative(final_result);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
