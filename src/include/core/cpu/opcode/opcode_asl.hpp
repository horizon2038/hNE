#ifndef CORE_OPCODE_ASL_HPP
#define CORE_OPCODE_ASL_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_asl final : public opcode
    {
      public:
        opcode_asl(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_asl() {};

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

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            if (!is_accumulator)
            {
                target_value = root_cpu.bus->read(fetched_address);
            }

            root_cpu.registers.carry = (target_value >> 7) & 1;
            target_value             = static_cast<uint8_t>(target_value << 1);

            if (is_accumulator)
            {
                root_cpu.registers.a = target_value;
            }
            else
            {
                root_cpu.bus->write(fetched_address, target_value);
            }

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
