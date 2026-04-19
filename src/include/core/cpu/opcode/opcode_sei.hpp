#ifndef CORE_OPCODE_SEI_HPP
#define CORE_OPCODE_SEI_HPP

#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_sei final : public opcode
    {
      public:
        opcode_sei(cpu &target_cpu);
        ~opcode_sei() {};

        void execute() override;

      private:
        cpu &root_cpu;
    };
}

#endif
