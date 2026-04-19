#ifndef CORE_OPCODE_JMP_HPP
#define CORE_OPCODE_JMP_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_jmp final : public opcode
    {
      public:
        opcode_jmp(addressing_mode init_addressing_mode, cpu &target_cpu);
        ~opcode_jmp() {};

        void execute() override;

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
