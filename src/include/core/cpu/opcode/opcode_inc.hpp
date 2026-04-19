#ifndef CORE_OPCODE_INC_HPP
#define CORE_OPCODE_INC_HPP

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>

namespace core
{
    class opcode_inc final : public opcode
    {
      public:
        opcode_inc(addressing_mode init_addressing_mode, cpu &target_cpu);
        ~opcode_inc() {};

        void execute() override;

      private:
        addressing_mode mode;
        cpu            &root_cpu;
    };
}

#endif
