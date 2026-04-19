#ifndef CORE_OPCODE_BNE_HPP
#define CORE_OPCODE_BNE_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_bne final : public opcode
    {
      public:
        opcode_bne(addressing_mode init_addressing_mode, cpu &target_cpu);
        ~opcode_bne() {};

        void execute() override;

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
