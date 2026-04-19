#ifndef CORE_OPCODE_EOR_HPP
#define CORE_OPCODE_EOR_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_eor final : public opcode
    {
      public:
        opcode_eor(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_eor() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode, true);
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

            root_cpu.registers.a ^= fetched_value;
            root_cpu.update_negative(root_cpu.registers.a);
            root_cpu.update_zero(root_cpu.registers.a);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
