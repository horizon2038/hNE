#ifndef CORE_OPCODE_CMP_HPP
#define CORE_OPCODE_CMP_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_cmp final : public opcode
    {
      public:
        opcode_cmp(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_cmp() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode, true);
            uint8_t target_value {};

            using enum addressing_mode;
            switch (mode)
            {
                case IMMEDIATE :
                    {
                        root_cpu.apply_cycles(2);
                        auto fetched_value = fetched_address & 0xFF;
                        target_value       = root_cpu.registers.a - fetched_value;

                        root_cpu.update_negative(target_value);
                        root_cpu.registers.zero  = (fetched_value == root_cpu.registers.a);
                        root_cpu.registers.carry = fetched_value <= root_cpu.registers.a;
                        return;
                    }

                case ZERO_PAGE :
                    root_cpu.apply_cycles(3);
                    break;

                case INDEXED_ZERO_PAGE_X :
                    root_cpu.apply_cycles(4);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(4);
                    break;

                case INDEXED_ABSOLUTE_X :
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

            auto fetched_value = root_cpu.bus->read(fetched_address);
            target_value       = root_cpu.registers.a - fetched_value;

            root_cpu.update_negative(target_value);
            root_cpu.registers.zero  = (fetched_value == root_cpu.registers.a);
            root_cpu.registers.carry = fetched_value <= root_cpu.registers.a;
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
