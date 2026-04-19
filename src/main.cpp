#include <memory>
#include <unistd.h>

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/opcode.hpp>
#include <core/cpu/opcode/opcode_none.hpp>
#include <core/io/bus/bus.hpp>
#include <core/io/io.hpp>
#include <core/io/io_stab.hpp>
#include <core/io/memory/ram.hpp>
#include <core/io/memory/rom.hpp>

// opcodes
#include <core/cpu/opcode/opcode_lda.hpp>
#include <core/cpu/opcode/opcode_ldx.hpp>
#include <core/cpu/opcode/opcode_ldy.hpp>

#include <core/cpu/opcode/opcode_sta.hpp>
#include <core/cpu/opcode/opcode_stx.hpp>
#include <core/cpu/opcode/opcode_sty.hpp>

#include <core/cpu/opcode/opcode_tax.hpp>
#include <core/cpu/opcode/opcode_tay.hpp>

#include <core/cpu/opcode/opcode_tsx.hpp>
#include <core/cpu/opcode/opcode_txa.hpp>
#include <core/cpu/opcode/opcode_txs.hpp>
#include <core/cpu/opcode/opcode_tya.hpp>

#include <core/cpu/opcode/opcode_adc.hpp>
#include <core/cpu/opcode/opcode_and.hpp>
#include <core/cpu/opcode/opcode_eor.hpp>

#include <core/cpu/opcode/opcode_asl.hpp>
#include <core/cpu/opcode/opcode_bit.hpp>
#include <core/cpu/opcode/opcode_bne.hpp>
#include <core/cpu/opcode/opcode_cmp.hpp>
#include <core/cpu/opcode/opcode_cpx.hpp>
#include <core/cpu/opcode/opcode_cpy.hpp>
#include <core/cpu/opcode/opcode_dec.hpp>
#include <core/cpu/opcode/opcode_dex.hpp>
#include <core/cpu/opcode/opcode_dey.hpp>
#include <core/cpu/opcode/opcode_inc.hpp>
#include <core/cpu/opcode/opcode_inx.hpp>
#include <core/cpu/opcode/opcode_iny.hpp>
#include <core/cpu/opcode/opcode_jmp.hpp>
#include <core/cpu/opcode/opcode_sei.hpp>

#include <core/cpu/opcode/opcode_brk.hpp>
#include <core/cpu/opcode/opcode_nop.hpp>

void init_opcodes(core::cpu &target_cpu)
{
    using enum core::addressing_mode;

    // LDA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(IMMEDIATE, target_cpu),
        0xA9
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(ZERO_PAGE, target_cpu),
        0xA5
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xB5
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(ABSOLUTE, target_cpu),
        0xAD
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_ABSOLUTE_X, target_cpu),
        0xBD
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xB9
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDEXED_INDIRECT, target_cpu),
        0xA1
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lda>(INDIRECT_INDEXED, target_cpu),
        0xB1
    );

    // LDX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(IMMEDIATE, target_cpu),
        0xA2
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(ZERO_PAGE, target_cpu),
        0xA6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(INDEXED_ZERO_PAGE_Y, target_cpu),
        0xB6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(ABSOLUTE, target_cpu),
        0xAE
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldx>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xBE
    );

    // LDY
    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(IMMEDIATE, target_cpu),
        0xA0
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(ZERO_PAGE, target_cpu),
        0xA4
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xB4
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(ABSOLUTE, target_cpu),
        0xAC
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ldy>(INDEXED_ABSOLUTE_X, target_cpu),
        0xBC
    );

    // STA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(ZERO_PAGE, target_cpu),
        0x85
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x95
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(ABSOLUTE, target_cpu),
        0x8D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_ABSOLUTE_X, target_cpu),
        0x9D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x99
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDEXED_INDIRECT, target_cpu),
        0x81
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sta>(INDIRECT_INDEXED, target_cpu),
        0x91
    );

    // STX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_stx>(ZERO_PAGE, target_cpu),
        0x86
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_stx>(INDEXED_ZERO_PAGE_Y, target_cpu),
        0x96
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_stx>(ABSOLUTE, target_cpu),
        0x8E
    );

    // STY
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sty>(ZERO_PAGE, target_cpu),
        0x84
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sty>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x94
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sty>(ABSOLUTE, target_cpu),
        0x8C
    );

    // TAX
    target_cpu.register_opcode(std::make_unique<core::opcode_tax>(target_cpu), 0xAA);

    // TAY
    target_cpu.register_opcode(std::make_unique<core::opcode_tay>(target_cpu), 0xA8);

    // TSX
    target_cpu.register_opcode(std::make_unique<core::opcode_tsx>(target_cpu), 0xBA);

    // TXA
    target_cpu.register_opcode(std::make_unique<core::opcode_txa>(target_cpu), 0x8A);

    // TXS
    target_cpu.register_opcode(std::make_unique<core::opcode_txs>(target_cpu), 0x9A);

    // TYA
    target_cpu.register_opcode(std::make_unique<core::opcode_tya>(target_cpu), 0x98);

    // ADC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(IMMEDIATE, target_cpu),
        0x69
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(ZERO_PAGE, target_cpu),
        0x65
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x75
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(ABSOLUTE, target_cpu),
        0x6D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(INDEXED_ABSOLUTE_X, target_cpu),
        0x7D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x79
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(INDEXED_INDIRECT, target_cpu),
        0x61
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_adc>(INDIRECT_INDEXED, target_cpu),
        0x71
    );

    // AND
    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(IMMEDIATE, target_cpu),
        0x29
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(ZERO_PAGE, target_cpu),
        0x25
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x35
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(ABSOLUTE, target_cpu),
        0x2D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(INDEXED_ABSOLUTE_X, target_cpu),
        0x3D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x39
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(INDEXED_INDIRECT, target_cpu),
        0x21
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_and>(INDIRECT_INDEXED, target_cpu),
        0x31
    );

    // ASL
    target_cpu.register_opcode(
        std::make_unique<core::opcode_asl>(ACCUMLATOR, target_cpu),
        0x0A
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_asl>(ZERO_PAGE, target_cpu),
        0x06
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_asl>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x16
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_asl>(ABSOLUTE, target_cpu),
        0x0E
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_asl>(INDEXED_ABSOLUTE_X, target_cpu),
        0x1E
    );

    // BIT
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bit>(ZERO_PAGE, target_cpu),
        0x24
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_bit>(ABSOLUTE, target_cpu),
        0x2C
    );

    // CMP
    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(IMMEDIATE, target_cpu),
        0xC9
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(ZERO_PAGE, target_cpu),
        0xC5
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xD5
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(ABSOLUTE, target_cpu),
        0xCD
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(INDEXED_ABSOLUTE_X, target_cpu),
        0xDD
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xD9
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(INDEXED_INDIRECT, target_cpu),
        0xC1
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cmp>(INDIRECT_INDEXED, target_cpu),
        0xD1
    );

    // CPX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_cpx>(IMMEDIATE, target_cpu),
        0xE0
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cpx>(ZERO_PAGE, target_cpu),
        0xE4
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cpx>(ABSOLUTE, target_cpu),
        0xEC
    );

    // CPY
    target_cpu.register_opcode(
        std::make_unique<core::opcode_cpy>(IMMEDIATE, target_cpu),
        0xC0
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cpy>(ZERO_PAGE, target_cpu),
        0xC4
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_cpy>(ABSOLUTE, target_cpu),
        0xCC
    );

    // DEC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dec>(ZERO_PAGE, target_cpu),
        0xC6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_dec>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xD6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_dec>(ABSOLUTE, target_cpu),
        0xCE
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_dec>(INDEXED_ABSOLUTE_X, target_cpu),
        0xDE
    );

    // DEX
    target_cpu.register_opcode(std::make_unique<core::opcode_dex>(target_cpu), 0xCA);

    // DEY
    target_cpu.register_opcode(std::make_unique<core::opcode_dey>(target_cpu), 0x88);

    // EOR
    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(IMMEDIATE, target_cpu),
        0x49
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(ZERO_PAGE, target_cpu),
        0x45
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x55
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(ABSOLUTE, target_cpu),
        0x4D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(INDEXED_ABSOLUTE_X, target_cpu),
        0x5D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x59
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(INDEXED_INDIRECT, target_cpu),
        0x41
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_eor>(INDIRECT_INDEXED, target_cpu),
        0x51
    );

    // INC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_inc>(ZERO_PAGE, target_cpu),
        0xE6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_inc>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xF6
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_inc>(ABSOLUTE, target_cpu),
        0xEE
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_inc>(INDEXED_ABSOLUTE_X, target_cpu),
        0xFE
    );

    // INX
    target_cpu.register_opcode(std::make_unique<core::opcode_inx>(target_cpu), 0xE8);

    // INY
    target_cpu.register_opcode(std::make_unique<core::opcode_iny>(target_cpu), 0xC8);

    // LSR
    // ORA
    // ROL
    // ROR
    // SBS
    //
    // PHA
    // PHP
    // PLA
    // PLP
    //
    // JMP
    target_cpu.register_opcode(
        std::make_unique<core::opcode_jmp>(ABSOLUTE, target_cpu),
        0x4C
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_jmp>(INDIRECT, target_cpu),
        0x6C
    );

    // JSR
    // RTS
    // RTI
    //
    // BCC
    // BCS
    // BEQ
    // BMI
    // BNE
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bne>(RELATIVE, target_cpu),
        0xD0
    );

    // BPL
    // BVC
    // BVS
    //
    // CLC
    // CLD
    // CLI
    // CLV
    // SEC
    // SED
    // SEI
    target_cpu.register_opcode(std::make_unique<core::opcode_sei>(target_cpu), 0x78);

    // BRK
    target_cpu.register_opcode(std::make_unique<core::opcode_brk>(target_cpu), 0x00);

    // NOP
    target_cpu.register_opcode(std::make_unique<core::opcode_nop>(target_cpu), 0xEA);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <rom_file>" << std::endl;
        return 1;
    }

    auto ram = std::make_unique<core::working_ram>();
    auto rom = std::make_unique<core::rom>(argv[1]);
    auto ppu = std::make_unique<core::io_stab>();
    auto bus = std::make_unique<core::bus>(
        std::move(ram),
        std::move(rom->charactor),
        std::move(rom->program),
        std::move(ppu)
    );

    auto cpu = std::make_unique<core::cpu>(std::move(bus));
    init_opcodes(*cpu.get());

    cpu->reset();
    for (;;)
    {
        cpu->clock();
        usleep(5000);
    }
}
