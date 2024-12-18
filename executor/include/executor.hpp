#pragma once

#include "hart.hpp"
#include "instruction.hpp"
#include "basic_block.hpp"

namespace sim {

class Executor {
   public:
    // R - type
    static void execute_add(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sub(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sll(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_slt(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sltu(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_xor(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_srl(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sra(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_or(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_and(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_addw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sllw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_srlw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_subw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sraw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sri(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sriw(Hart &hart, const EncInstr *instructions, size_t instr_index);



    // I - type
    static void execute_jalr(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_lb(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_lh(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_lw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_lbu(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_lhu(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_addi(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_slti(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sltiu(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_xori(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_ori(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_andi(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_lwu(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_ld(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_slli(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_srli(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_srai(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_addiw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_slliw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_srliw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sraiw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    // static void execute_ecall(Hart &hart, const EncInstr *instructions, size_t instr_index);
    // static void execute_ebreak(Hart &hart, const EncInstr *instructions, size_t instr_index);
    // static void execute_fence(Hart &hart, const EncInstr *instructions, size_t instr_index);
    // static void execute_fence_i(Hart &hart, const EncInstr *instructions, size_t instr_index);

    // static void execute_pause(Hart &hart, const EncInstr *instructions, size_t instr_index);

    // S - type
    static void execute_sb(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sh(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sw(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_sd(Hart &hart, const EncInstr *instructions, size_t instr_index);

    // B - type
    static void execute_beq(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_bne(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_blt(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_bge(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_bltu(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_bgeu(Hart &hart, const EncInstr *instructions, size_t instr_index);

    // U - type
    static void execute_lui(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static void execute_auipc(Hart &hart, const EncInstr *instructions, size_t instr_index);

    // J - type
    static void execute_jal(Hart &hart, const EncInstr *instructions, size_t instr_index);

    static void execute_ecall(Hart &hart, const EncInstr *instructions, size_t instr_index);

    static void execute_fake_bb_end(Hart &hart, const EncInstr *instructions, size_t instr_index);

    static bool execute_BB(Hart &hart, BasicBlock &bb);

    using executor_func_t = void (*)(Hart &hart, const EncInstr *instructions, size_t instr_index);
    static const std::array<Executor::executor_func_t, 51> functions;

    static bool run(Hart &hart, size_t &instr_counter);
};

}  // namespace sim
