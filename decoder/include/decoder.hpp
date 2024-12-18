#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "instruction.hpp"

namespace sim {

constexpr size_t kOpcodeNum = 1 << 7;

class Decoder final {
   private:

    static const std::unordered_map<int, instr_t> m_mask;

    enum class Match : instr_t;

    // static void decode_r_type(instr_t raw_instr, EncInstr &enc_instr);
    // static void decode_i_type(instr_t raw_instr, EncInstr &enc_instr);
    // static void decode_s_type(instr_t raw_instr, EncInstr &enc_instr);
    // static void decode_b_type(instr_t raw_instr, EncInstr &enc_instr);
    // static void decode_u_type(instr_t raw_instr, EncInstr &enc_instr);
    // static void decode_j_type(instr_t raw_instr, EncInstr &enc_instr);

   public:
    static void decode_instruction(instr_t raw_instr, EncInstr &enc_instr);
};

}  // namespace sim
