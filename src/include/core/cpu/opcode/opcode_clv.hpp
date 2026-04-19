#ifndef CORE_OPCODE_CLV_HPP
#define CORE_OPCODE_CLV_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_clv final : public opcode
    {
      public:
        opcode_clv(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_clv() {};

        void execute() override
        {
            root_cpu.registers.overflow = false;
            root_cpu.apply_cycles(2);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
