#ifndef CORE_OPCODE_INX_HPP
#define CORE_OPCODE_INX_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_inx final : public opcode
    {
      public:
        opcode_inx(cpu &target_cpu);
        ~opcode_inx() {};

        void execute() override;

      private:
        cpu &root_cpu;
    };
}

#endif
