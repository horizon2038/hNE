#include <memory>

#include <core/cpu/adressing.hpp>
#include <core/cpu/cpu.hpp>
#include <core/cpu/opcode/init_opcodes.hpp>

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
#include <core/cpu/opcode/opcode_bcc.hpp>
#include <core/cpu/opcode/opcode_bcs.hpp>
#include <core/cpu/opcode/opcode_beq.hpp>
#include <core/cpu/opcode/opcode_bit.hpp>
#include <core/cpu/opcode/opcode_bmi.hpp>
#include <core/cpu/opcode/opcode_bne.hpp>
#include <core/cpu/opcode/opcode_bpl.hpp>
#include <core/cpu/opcode/opcode_bvc.hpp>
#include <core/cpu/opcode/opcode_bvs.hpp>
#include <core/cpu/opcode/opcode_clc.hpp>
#include <core/cpu/opcode/opcode_cld.hpp>
#include <core/cpu/opcode/opcode_cli.hpp>
#include <core/cpu/opcode/opcode_clv.hpp>
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
#include <core/cpu/opcode/opcode_jsr.hpp>
#include <core/cpu/opcode/opcode_lsr.hpp>
#include <core/cpu/opcode/opcode_ora.hpp>
#include <core/cpu/opcode/opcode_pha.hpp>
#include <core/cpu/opcode/opcode_php.hpp>
#include <core/cpu/opcode/opcode_pla.hpp>
#include <core/cpu/opcode/opcode_plp.hpp>
#include <core/cpu/opcode/opcode_rol.hpp>
#include <core/cpu/opcode/opcode_ror.hpp>
#include <core/cpu/opcode/opcode_rti.hpp>
#include <core/cpu/opcode/opcode_rts.hpp>
#include <core/cpu/opcode/opcode_sbc.hpp>
#include <core/cpu/opcode/opcode_sec.hpp>
#include <core/cpu/opcode/opcode_sed.hpp>
#include <core/cpu/opcode/opcode_sei.hpp>

#include <core/cpu/opcode/opcode_brk.hpp>
#include <core/cpu/opcode/opcode_nop.hpp>

#include <core/cpu/opcode/opcode_dcp.hpp>
#include <core/cpu/opcode/opcode_isb.hpp>
#include <core/cpu/opcode/opcode_lax.hpp>
#include <core/cpu/opcode/opcode_rla.hpp>
#include <core/cpu/opcode/opcode_rra.hpp>
#include <core/cpu/opcode/opcode_sax.hpp>
#include <core/cpu/opcode/opcode_slo.hpp>
#include <core/cpu/opcode/opcode_sre.hpp>

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
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lsr>(ACCUMLATOR, target_cpu),
        0x4A
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_lsr>(ZERO_PAGE, target_cpu),
        0x46
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_lsr>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x56
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_lsr>(ABSOLUTE, target_cpu),
        0x4E
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_lsr>(INDEXED_ABSOLUTE_X, target_cpu),
        0x5E
    );

    // ORA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(IMMEDIATE, target_cpu),
        0x09
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(ZERO_PAGE, target_cpu),
        0x05
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x15
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(ABSOLUTE, target_cpu),
        0x0D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(INDEXED_ABSOLUTE_X, target_cpu),
        0x1D
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x19
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(INDEXED_INDIRECT, target_cpu),
        0x01
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ora>(INDIRECT_INDEXED, target_cpu),
        0x11
    );

    // ROL
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rol>(ACCUMLATOR, target_cpu),
        0x2A
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_rol>(ZERO_PAGE, target_cpu),
        0x26
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_rol>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x36
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_rol>(ABSOLUTE, target_cpu),
        0x2E
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_rol>(INDEXED_ABSOLUTE_X, target_cpu),
        0x3E
    );

    // ROR
    target_cpu.register_opcode(
        std::make_unique<core::opcode_ror>(ACCUMLATOR, target_cpu),
        0x6A
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ror>(ZERO_PAGE, target_cpu),
        0x66
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ror>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x76
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ror>(ABSOLUTE, target_cpu),
        0x6E
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_ror>(INDEXED_ABSOLUTE_X, target_cpu),
        0x7E
    );

    // SBC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(IMMEDIATE, target_cpu),
        0xE9
    );

    // unofficial SBC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(IMMEDIATE, target_cpu),
        0xEB
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(ZERO_PAGE, target_cpu),
        0xE5
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xF5
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(ABSOLUTE, target_cpu),
        0xED
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(INDEXED_ABSOLUTE_X, target_cpu),
        0xFD
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xF9
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(INDEXED_INDIRECT, target_cpu),
        0xE1
    );

    target_cpu.register_opcode(
        std::make_unique<core::opcode_sbc>(INDIRECT_INDEXED, target_cpu),
        0xF1
    );

    //
    // PHA
    target_cpu.register_opcode(std::make_unique<core::opcode_pha>(target_cpu), 0x48);

    // PHP
    target_cpu.register_opcode(std::make_unique<core::opcode_php>(target_cpu), 0x08);

    // PLA
    target_cpu.register_opcode(std::make_unique<core::opcode_pla>(target_cpu), 0x68);

    // PLP
    target_cpu.register_opcode(std::make_unique<core::opcode_plp>(target_cpu), 0x28);

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
    target_cpu.register_opcode(
        std::make_unique<core::opcode_jsr>(ABSOLUTE, target_cpu),
        0x20
    );

    // RTS
    target_cpu.register_opcode(std::make_unique<core::opcode_rts>(target_cpu), 0x60);

    // RTI
    target_cpu.register_opcode(std::make_unique<core::opcode_rti>(target_cpu), 0x40);

    //
    // BCC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bcc>(RELATIVE, target_cpu),
        0x90
    );

    // BCS
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bcs>(RELATIVE, target_cpu),
        0xB0
    );

    // BEQ
    target_cpu.register_opcode(
        std::make_unique<core::opcode_beq>(RELATIVE, target_cpu),
        0xF0
    );

    // BMI
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bmi>(RELATIVE, target_cpu),
        0x30
    );

    // BNE
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bne>(RELATIVE, target_cpu),
        0xD0
    );

    // BPL
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bpl>(RELATIVE, target_cpu),
        0x10
    );

    // BVC
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bvc>(RELATIVE, target_cpu),
        0x50
    );

    // BVS
    target_cpu.register_opcode(
        std::make_unique<core::opcode_bvs>(RELATIVE, target_cpu),
        0x70
    );

    //
    // CLC
    target_cpu.register_opcode(std::make_unique<core::opcode_clc>(target_cpu), 0x18);

    // CLD
    target_cpu.register_opcode(std::make_unique<core::opcode_cld>(target_cpu), 0xD8);

    // CLI
    target_cpu.register_opcode(std::make_unique<core::opcode_cli>(target_cpu), 0x58);

    // CLV
    target_cpu.register_opcode(std::make_unique<core::opcode_clv>(target_cpu), 0xB8);

    // SEC
    target_cpu.register_opcode(std::make_unique<core::opcode_sec>(target_cpu), 0x38);

    // SED
    target_cpu.register_opcode(std::make_unique<core::opcode_sed>(target_cpu), 0xF8);

    // SEI
    target_cpu.register_opcode(std::make_unique<core::opcode_sei>(target_cpu), 0x78);

    // BRK
    target_cpu.register_opcode(std::make_unique<core::opcode_brk>(target_cpu), 0x00);

    // NOP
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0xEA
    );

    // undocumented NOP (implied)
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0x1A
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0x3A
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0x5A
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0x7A
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0xDA
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMPLIED, target_cpu),
        0xFA
    );

    // undocumented NOP (immediate)
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMMEDIATE, target_cpu),
        0x80
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMMEDIATE, target_cpu),
        0x82
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMMEDIATE, target_cpu),
        0x89
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMMEDIATE, target_cpu),
        0xC2
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(IMMEDIATE, target_cpu),
        0xE2
    );

    // undocumented NOP (zero page)
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(ZERO_PAGE, target_cpu),
        0x04
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(ZERO_PAGE, target_cpu),
        0x44
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(ZERO_PAGE, target_cpu),
        0x64
    );

    // undocumented NOP (zero page,X)
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x14
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x34
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x54
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x74
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xD4
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xF4
    );

    // undocumented NOP (absolute)
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(ABSOLUTE, target_cpu),
        0x0C
    );

    // undocumented NOP (absolute,X) ※page crossingで+1cycle発生するタイプ
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ABSOLUTE_X, target_cpu),
        0x1C
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ABSOLUTE_X, target_cpu),
        0x3C
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ABSOLUTE_X, target_cpu),
        0x5C
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ABSOLUTE_X, target_cpu),
        0x7C
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ABSOLUTE_X, target_cpu),
        0xDC
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_nop>(INDEXED_ABSOLUTE_X, target_cpu),
        0xFC
    );

    // LAX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lax>(ZERO_PAGE, target_cpu),
        0xA7
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lax>(INDEXED_ZERO_PAGE_Y, target_cpu),
        0xB7
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lax>(ABSOLUTE, target_cpu),
        0xAF
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lax>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xBF
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lax>(INDEXED_INDIRECT, target_cpu),
        0xA3
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_lax>(INDIRECT_INDEXED, target_cpu),
        0xB3
    );

    // SAX
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sax>(ZERO_PAGE, target_cpu),
        0x87
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sax>(INDEXED_ZERO_PAGE_Y, target_cpu),
        0x97
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sax>(ABSOLUTE, target_cpu),
        0x8F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sax>(INDEXED_INDIRECT, target_cpu),
        0x83
    );

    // DCP
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(ZERO_PAGE, target_cpu),
        0xC7
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xD7
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(ABSOLUTE, target_cpu),
        0xCF
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(INDEXED_ABSOLUTE_X, target_cpu),
        0xDF
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xDB
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(INDEXED_INDIRECT, target_cpu),
        0xC3
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_dcp>(INDIRECT_INDEXED, target_cpu),
        0xD3
    );

    // ISB
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(ZERO_PAGE, target_cpu),
        0xE7
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(INDEXED_ZERO_PAGE_X, target_cpu),
        0xF7
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(ABSOLUTE, target_cpu),
        0xEF
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(INDEXED_ABSOLUTE_X, target_cpu),
        0xFF
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(INDEXED_ABSOLUTE_Y, target_cpu),
        0xFB
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(INDEXED_INDIRECT, target_cpu),
        0xE3
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_isb>(INDIRECT_INDEXED, target_cpu),
        0xF3
    );

    // SLO
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(ZERO_PAGE, target_cpu),
        0x07
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x17
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(ABSOLUTE, target_cpu),
        0x0F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(INDEXED_ABSOLUTE_X, target_cpu),
        0x1F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x1B
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(INDEXED_INDIRECT, target_cpu),
        0x03
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_slo>(INDIRECT_INDEXED, target_cpu),
        0x13
    );

    // RLA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(ZERO_PAGE, target_cpu),
        0x27
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x37
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(ABSOLUTE, target_cpu),
        0x2F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(INDEXED_ABSOLUTE_X, target_cpu),
        0x3F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x3B
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(INDEXED_INDIRECT, target_cpu),
        0x23
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rla>(INDIRECT_INDEXED, target_cpu),
        0x33
    );

    // SRE
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(ZERO_PAGE, target_cpu),
        0x47
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x57
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(ABSOLUTE, target_cpu),
        0x4F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(INDEXED_ABSOLUTE_X, target_cpu),
        0x5F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x5B
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(INDEXED_INDIRECT, target_cpu),
        0x43
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_sre>(INDIRECT_INDEXED, target_cpu),
        0x53
    );

    // RRA
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(ZERO_PAGE, target_cpu),
        0x67
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(INDEXED_ZERO_PAGE_X, target_cpu),
        0x77
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(ABSOLUTE, target_cpu),
        0x6F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(INDEXED_ABSOLUTE_X, target_cpu),
        0x7F
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(INDEXED_ABSOLUTE_Y, target_cpu),
        0x7B
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(INDEXED_INDIRECT, target_cpu),
        0x63
    );
    target_cpu.register_opcode(
        std::make_unique<core::opcode_rra>(INDIRECT_INDEXED, target_cpu),
        0x73
    );
}
