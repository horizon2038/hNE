#ifndef CORE_OPCODE_ROL_HPP
#define CORE_OPCODE_ROL_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_rol final : public opcode
    {
      public:
        opcode_rol(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_rol() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t target_value {};
            bool    is_accumulator = false;

            using enum addressing_mode;
            switch (mode)
            {
                case ACCUMLATOR :
                    root_cpu.apply_cycles(2);
                    target_value    = root_cpu.registers.a;
                    is_accumulator  = true;
                    break;

                case ZERO_PAGE :
                    root_cpu.apply_cycles(5);
                    target_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDEXED_ZERO_PAGE_X :
                    root_cpu.apply_cycles(6);
                    target_value = root_cpu.bus->read(fetched_address);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(6);
                    target_value = root_cpu.bus->read(fetched_address);
                    break;

                case INDEXED_ABSOLUTE_X :
                    root_cpu.apply_cycles(7);
                    target_value = root_cpu.bus->read(fetched_address);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            auto previous_carry    = static_cast<uint8_t>(root_cpu.registers.carry);
            root_cpu.registers.carry = (target_value >> 7) & 0x01;
            target_value = static_cast<uint8_t>((target_value << 1) | previous_carry);

            if (is_accumulator)
            {
                root_cpu.registers.a = target_value;
            }
            else
            {
                root_cpu.bus->write(fetched_address, target_value);
            }

            root_cpu.update_negative(target_value);
            root_cpu.update_zero(target_value);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
