#include "decoder.hpp"

#include <fmt/format.h>

#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "common.hpp"
#include "instruction.hpp"
#include "executor.hpp"
#include "logger.hpp"
#include <unordered_map>

#define CONCAT(A,B)                A##B
#define EXPAND_CONCAT(A,B)         CONCAT(A,B)
#define MATCH_PREFIX               Match::
#define INSTID_PREFIX              InstrId::

#define ENUM_MATCH(name)    Match::name
#define ENUM_INSTID(name)   InstrId::name
#define EXEC_FUNC(name)   Executor::name

namespace sim {

const std::unordered_map<int, instr_t> Decoder::m_mask{{
    {0b0000011, 0x707f},  // LOAD
    // [0b0001111] = 0x707f,      // MISC-MEM
    {0b0010011, 0x707f},      // OP-IMM
    {0b0011011, 0x707f},      // OP-IMM-32
    {0b0010111, 0x7f},        // AUIPC
    {0b0100011, 0x707f},      // STORE
    {0b0110011, 0xfe00707f},  // OP
    {0b0110111, 0x7f},        // LUI
    {0b0111011, 0xfe00707f},  // OP-32
    {0b1100011, 0x707f},      // BRANCH
    {0b1100111, 0x707f},      // JALR
    {0b1101111, 0x7f},        // JAL
    {0b1110011, 0x707f},      // SYSTEM
}};

enum class Decoder::Match : instr_t {  // MATCH
    // LUI
    LUI = 0x37,

    // AUIPC
    AUIPC = 0x17,

    // JAL
    JAL = 0x6f,

    // JALR
    JALR = 0x67,

    // BRANCH
    BEQ = 0x63,
    BNE = 0x1063,
    BLT = 0x4063,
    BGE = 0x5063,
    BLTU = 0x6063,
    BGEU = 0x7063,

    // LOAD
    LB = 0x3,
    LH = 0x1003,
    LW = 0x2003,
    LBU = 0x4003,
    LHU = 0x5003,
    LWU = 0x6003,
    LD = 0x3003,

    // STORE
    SB = 0x23,
    SH = 0x1023,
    SW = 0x2023,
    SD = 0x3023,

    // OP-IMM
    ADDI = 0x13,
    SLTI = 0x2013,
    SLTIU = 0x3013,
    ANDI = 0x7013,
    ORI = 0x6013,
    XORI = 0x4013,
    SLLI = 0x1013,
    // SRAI = 0x5013,

    // OP-IMM-32
    ADDIW = 0x1b,
    SLLIW = 0x101b,

    // OP
    ADD = 0x33,
    SLT = 0x2033,
    SLTU = 0x3033,
    AND = 0x7033,
    OR = 0x6033,
    XOR = 0x4033,
    SLL = 0x1033,
    SRL = 0x5033,
    SUB = 0x40000033,
    SRA = 0x40005033,

    // MISC-MEM
    // FENCE = 0xf,
    // FENCE_I = 0x100f,

    // SYSTEM
    ECALL = 0x73,
    // EBREAK = 0x100073,

    // OP-32
    ADDW = 0x3b,
    SUBW = 0x4000003b,
    SLLW = 0x103b,
    SRLW = 0x503b,
    SRAW = 0x4000503b,

    FAKE_BB_END
};

const int SRI_MATCH = 0x5013;  // combination of SRLI and SRAI
const int SRIW_MATCH = 0x501b;  // combination of SRLIW and SRAIW

void Decoder::decode_instruction(instr_t raw_instr, EncInstr &enc_instr) try {
    auto opcode = bits<6, 0>(raw_instr);

    instr_t match = raw_instr & m_mask.at(opcode);
    if (match == SRI_MATCH) {
        enc_instr.decodeRawI(InstrId::SRAI, raw_instr, Executor::execute_sri);
    } else if (match == SRIW_MATCH) {
        enc_instr.decodeRawI(InstrId::SRAIW, raw_instr, Executor::execute_sriw);
    }

    auto match_id = static_cast<Match>(match);

    switch (match_id) {
    #define DEFINE_INSTR(name, type, exec) \
        case ENUM_MATCH(name): \
        enc_instr.decodeRaw##type(ENUM_INSTID(name), raw_instr, &EXEC_FUNC(exec)); \
        break;
    #include "defines.hpp"
    #undef DEFINE_INSTR
    }
    // Logger &myLogger = Logger::getInstance();
    // myLogger.message(Logger::severity_level::standard, "Decoder",
    //                  fmt::format("Match {} {:#08x}\n", InstrName[enc_instr.id], raw_instr));

} catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
}

}  // namespace sim
