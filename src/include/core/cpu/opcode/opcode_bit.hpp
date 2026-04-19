#ifndef CORE_OPCODE_BIT_HPP
#define CORE_OPCODE_BIT_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_bit final : public opcode
    {
      public:
        opcode_bit(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_bit() {};

        void execute() override
        {
            auto    fetched_address = root_cpu.fetch_operand_address(mode);
            uint8_t fetched_value {};
            uint8_t and_result {};

            using enum addressing_mode;
            switch (mode)
            {
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

            fetched_value = root_cpu.bus->read(fetched_address);
            and_result    = root_cpu.registers.a & fetched_value;

            // flag
            root_cpu.registers.overflow = (fetched_value >> 6) & 1;
            root_cpu.update_negative(fetched_value);
            root_cpu.update_zero(and_result);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
