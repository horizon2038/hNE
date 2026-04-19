#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>

#include <core/common/common.hpp>
#include <core/cpu/adressing.hpp>
#include <core/cpu/hardware_context.hpp>
#include <core/cpu/opcode/opcode.hpp>
#include <core/io/io.hpp>

#include <memory>

namespace core
{
    static constexpr uint16_t OPCODE_COUNT_MAX = 256;

    // RP2A03
    class cpu
    {
      public:
        cpu(std::unique_ptr<io> target_bus);
        ~cpu();

        hardware_context    registers;
        std::unique_ptr<io> bus;

        void clock();

        uint8_t fetch();
        void    execute(uint8_t target_opcode);

        uint16_t fetch_operand_address(addressing_mode);
        void     apply_cycles(uint8_t cycles);

        // flag
        void update_negative(uint8_t target_register);
        void update_zero(uint8_t target_register);

        void    push(uint8_t data);
        uint8_t pop();

        // interrupt
        void register_opcode(std::unique_ptr<opcode> target_opcode, uint16_t opcode_number);

        void reset();
        void nmi();
        void irq();
        void brk();

        // debug
        void print_cpu_status();

      private:
        uint8_t                 cycles;
        std::unique_ptr<opcode> opcodes[OPCODE_COUNT_MAX];

        // init
        void init_opcodes();

        bool is_cycle_running();

        uint16_t fetch_interrupt_handler_address(address lower_address, address higher_address);
        void     save_interrupt_frame(bool break_mode);
        void     restore_interrupt_frame();
    };
}

#endif
