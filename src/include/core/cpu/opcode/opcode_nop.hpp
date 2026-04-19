#ifndef CORE_OPCODE_NOP_HPP
#define CORE_OPCODE_NOP_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

#include <iostream>

namespace core
{
    class opcode_nop final : public opcode
    {
      public:
        opcode_nop(addressing_mode init_addressing_mode, cpu &target_cpu)
            : mode { init_addressing_mode }
            , root_cpu { target_cpu }
        {
        }

        ~opcode_nop() override = default;

        void execute() override
        {
            using enum addressing_mode;

            switch (mode)
            {
                case IMPLIED :
                    {
                        root_cpu.apply_cycles(2);
                        return;
                    }

                case IMMEDIATE :
                    {
                        root_cpu.apply_cycles(2);
                        (void)root_cpu.fetch_operand_address(mode);
                        return;
                    }

                case ZERO_PAGE :
                    {
                        root_cpu.apply_cycles(3);
                        (void)root_cpu.fetch_operand_address(mode);
                        return;
                    }

                case INDEXED_ZERO_PAGE_X :
                    {
                        root_cpu.apply_cycles(4);
                        (void)root_cpu.fetch_operand_address(mode);
                        return;
                    }

                case ABSOLUTE :
                    {
                        root_cpu.apply_cycles(4);
                        (void)root_cpu.fetch_operand_address(mode);
                        return;
                    }

                case INDEXED_ABSOLUTE_X :
                    {
                        root_cpu.apply_cycles(4);
                        (void)root_cpu.fetch_operand_address(mode);
                        return;
                    }

                default :
                    {
                        std::cout << "error : unsupported nop addressing mode";
                        return;
                    }
            }
        }

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
