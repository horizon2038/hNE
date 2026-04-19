#ifndef CORE_OPCODE_STA_HPP
#define CORE_OPCODE_STA_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_sta final : public opcode
    {
      public:
        opcode_sta(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu } {};
        ~opcode_sta() {};

        void execute() override
        {
            auto fetched_address = root_cpu.fetch_operand_address(mode);

            using enum addressing_mode;
            switch (mode)
            {
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
                    root_cpu.apply_cycles(5);
                    break;

                case INDEXED_ABSOLUTE_Y :
                    root_cpu.apply_cycles(5);
                    break;

                case INDEXED_INDIRECT :
                    root_cpu.apply_cycles(6);
                    break;

                case INDIRECT_INDEXED :
                    root_cpu.apply_cycles(6);
                    break;

                default :
                    std::cout << "error : unsupported addressing mode";
                    return;
            }

            root_cpu.bus->write(fetched_address, root_cpu.registers.a);
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
