#ifndef OPCODE_NONE_HPP
#define OPCODE_NONE_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_none final : public opcode
    {
      public:
        opcode_none(core::cpu &target_cpu);
        ~opcode_none() {};

        void execute() override;

      private:
        core::cpu &_cpu;
    };
}

#endif
