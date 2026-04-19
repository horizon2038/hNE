#ifndef CORE_OPCODE_SBC_HPP
#define CORE_OPCODE_SBC_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_sbc final : public opcode
    {
      public:
        opcode_sbc(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_sbc() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t fetched_value {};

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

            uint16_t accumlator = root_cpu.registers.a;
            uint16_t borrow = root_cpu.registers.carry ? 0 : 1;
            uint16_t result = accumlator - fetched_value - borrow;
            uint8_t  result_8bit = static_cast<uint8_t>(result & 0xFF);

            root_cpu.registers.carry
                = (accumlator >= (static_cast<uint16_t>(fetched_value) + borrow));
            root_cpu.registers.overflow = ((accumlator ^ result_8bit)
                                           & (accumlator ^ fetched_value) & 0x80)
                                        != 0;
            root_cpu.registers.a = result_8bit;
            root_cpu.update_negative(result_8bit);
            root_cpu.update_zero(result_8bit);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
