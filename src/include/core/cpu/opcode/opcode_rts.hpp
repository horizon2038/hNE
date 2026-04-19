#ifndef CORE_OPCODE_RTS_HPP
#define CORE_OPCODE_RTS_HPP

#include <core/common/common.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_rts final : public opcode
    {
      public:
        opcode_rts(cpu &target_cpu) : root_cpu { target_cpu } {};
        ~opcode_rts() {};

        void execute() override
        {
            auto lower_address    = root_cpu.pop();
            auto higher_address   = root_cpu.pop();

            root_cpu.registers.pc = static_cast<uint16_t>(merge_address(lower_address, higher_address) + 1);
            root_cpu.apply_cycles(6);
        }

      private:
        cpu &root_cpu;
    };
}

#endif
