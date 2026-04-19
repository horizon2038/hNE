#ifndef CORE_OPCODE_SAX_HPP
#define CORE_OPCODE_SAX_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_sax final : public opcode
    {
      public:
        opcode_sax(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu }
        {
        }

        ~opcode_sax() override = default;

        void execute() override
        {
            using enum addressing_mode;

            switch (mode)
            {
                case ZERO_PAGE :
                    root_cpu.apply_cycles(3);
                    break;

                case INDEXED_ZERO_PAGE_Y :
                    root_cpu.apply_cycles(4);
                    break;

                case ABSOLUTE :
                    root_cpu.apply_cycles(4);
                    break;

                case INDEXED_INDIRECT :
                    root_cpu.apply_cycles(6);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            auto fetched_address = root_cpu.fetch_operand_address(mode);
            auto target_value    = static_cast<uint8_t>(root_cpu.registers.a & root_cpu.registers.x);

            root_cpu.bus->write(fetched_address, target_value);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
