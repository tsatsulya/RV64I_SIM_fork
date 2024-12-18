// #define DEFINE_INSTR(name, type, exec)
//     case MATCH::#name:
//     enc_instr = EncInstr_##type(InstrId::#name, raw_instr, exec);
//     DEB("RS1 RS2 RD IMM: " << (int)ptr->rs1 << ' ' << (int)ptr->rs2 << ' ' << (int)ptr->rd << ' ' << (int)ptr->imm)
//     return OK;
// #include "instrs.h"


DEFINE_INSTR(ADD, R, execute_add)
DEFINE_INSTR(SUB, R, execute_sub)
DEFINE_INSTR(SLL, R, execute_sll)
DEFINE_INSTR(SLT, R, execute_slt)
DEFINE_INSTR(SLTU, R, execute_sltu)
DEFINE_INSTR(XOR, R, execute_xor)
DEFINE_INSTR(SRL, R, execute_srl)
DEFINE_INSTR(SRA, R, execute_sra)
DEFINE_INSTR(OR, R, execute_or)
DEFINE_INSTR(AND, R, execute_and)
DEFINE_INSTR(ADDW, R, execute_addw)
DEFINE_INSTR(SLLW, R, execute_sllw)
DEFINE_INSTR(SRLW, R, execute_srlw)
DEFINE_INSTR(SUBW, R, execute_subw)
DEFINE_INSTR(SRAW, R, execute_sraw)

// I - type
DEFINE_INSTR(JALR, I, execute_jalr)
DEFINE_INSTR(LB, I, execute_lb)
DEFINE_INSTR(LH, I, execute_lh)
DEFINE_INSTR(LW, I, execute_lw)
DEFINE_INSTR(LBU, I, execute_lbu)
DEFINE_INSTR(LHU, I, execute_lhu)
DEFINE_INSTR(ADDI, I, execute_addi)
DEFINE_INSTR(SLTI, I, execute_slti)
DEFINE_INSTR(SLTIU, I, execute_sltiu)
DEFINE_INSTR(XORI, I, execute_xori)
DEFINE_INSTR(ORI, I, execute_ori)
DEFINE_INSTR(ANDI, I, execute_andi)
DEFINE_INSTR(LWU, I, execute_lwu)
DEFINE_INSTR(LD, I, execute_ld)
DEFINE_INSTR(SLLI, I, execute_slli)
// DEFINE_INSTR(SRLI, I, execute_srli)
// DEFINE_INSTR(SRAI, I, execute_srai)
DEFINE_INSTR(ADDIW, I, execute_addiw)
DEFINE_INSTR(SLLIW, I, execute_slliw)
// DEFINE_INSTR(SRLIW, I, execute_srliw)
// DEFINE_INSTR(SRAIW, I, execute_sraiw)

// S - type
DEFINE_INSTR(SB, S, execute_sb)
DEFINE_INSTR(SH, S, execute_sh)
DEFINE_INSTR(SW, S, execute_sw)
DEFINE_INSTR(SD, S, execute_sd)

// B - type
DEFINE_INSTR(BEQ, B, execute_beq)
DEFINE_INSTR(BNE, B, execute_bne)
DEFINE_INSTR(BLT, B, execute_blt)
DEFINE_INSTR(BGE, B, execute_bge)
DEFINE_INSTR(BLTU, B, execute_bltu)
DEFINE_INSTR(BGEU, B, execute_bgeu)

// U - type
DEFINE_INSTR(LUI, U, execute_lui)
DEFINE_INSTR(AUIPC, U, execute_auipc)

// J - type
DEFINE_INSTR(JAL, J, execute_jal)
DEFINE_INSTR(FAKE_BB_END, J, execute_fake_bb_end)
DEFINE_INSTR(ECALL, J, execute_ecall)
