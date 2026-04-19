#ifndef CORE_OPCODE_ADC_HPP
#define CORE_OPCODE_ADC_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_adc final : public opcode
    {
      public:
        opcode_adc(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_adc() {};

        void execute() override
        {
            auto     fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t  fetched_value {};
            uint16_t result_value {}; // for carry
                                      //
            bool is_a_signed             = false;
            bool is_fetched_value_signed = false;
            bool is_result_signed        = false;

            is_a_signed                  = static_cast<bool>((root_cpu.registers.a >> 7) & 1);

            using enum addressing_mode;
            switch (mode)
            {
                case IMMEDIATE :
                    root_cpu.apply_cycles(2);
                    fetched_value = static_cast<uint8_t>(fetched_address & 0xFF);
                    break;

                case ZERO_PAGE :
                    root_cpu.apply_cycles(3);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDEXED_ZERO_PAGE_X :
                    root_cpu.apply_cycles(4);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(4);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDEXED_ABSOLUTE_X :
                    root_cpu.apply_cycles(4);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDEXED_ABSOLUTE_Y :
                    root_cpu.apply_cycles(4);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDEXED_INDIRECT :
                    root_cpu.apply_cycles(6);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDIRECT_INDEXED :
                    root_cpu.apply_cycles(5);
                    fetched_value = root_cpu.bus->read(fetched_address);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            is_fetched_value_signed = static_cast<bool>((fetched_value >> 7) & 1);

            result_value = static_cast<uint16_t>(fetched_value & 0xFF) + static_cast<uint16_t>(root_cpu.registers.a)
                         + static_cast<uint16_t>(root_cpu.registers.carry);

            is_result_signed     = static_cast<bool>((result_value >> 7) & 1);
            root_cpu.registers.a = static_cast<uint8_t>(result_value & 0xFF);

            // update flag
            root_cpu.update_negative(root_cpu.registers.a);
            root_cpu.registers.overflow = (is_a_signed == is_fetched_value_signed) && (is_a_signed != is_result_signed);
            root_cpu.registers.carry    = result_value > 0xFF;
            root_cpu.update_zero(root_cpu.registers.a);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
