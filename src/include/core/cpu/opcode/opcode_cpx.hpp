#ifndef CORE_OPCODE_CPX_HPP
#define CORE_OPCODE_CPX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_cpx final : public opcode
    {
      public:
        opcode_cpx(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_cpx() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t target_value {};

            using enum addressing_mode;
            switch (mode)
            {
                case IMMEDIATE :
                    {
                        root_cpu.apply_cycles(2);
                        auto fetched_value      = fetched_address & 0xFF;
                        target_value            = root_cpu.registers.x - fetched_value;

                        root_cpu.registers.zero = (fetched_value == root_cpu.registers.x);
                        root_cpu.update_negative(target_value);
                        root_cpu.registers.carry = fetched_value <= root_cpu.registers.x;
                        return;
                    }

                case ZERO_PAGE :
                    root_cpu.apply_cycles(3);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(4);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            auto fetched_value = root_cpu.bus->read(fetched_address);
            target_value       = root_cpu.registers.x - fetched_value;

            root_cpu.update_negative(target_value);
            root_cpu.registers.zero  = (fetched_value == root_cpu.registers.x);
            root_cpu.registers.carry = fetched_value <= root_cpu.registers.x;
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
