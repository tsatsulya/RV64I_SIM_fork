#pragma once

#include <stdint.h>

#include <sstream>
#include <string>
#include <iostream>
#include <string_view>
#include <functional>

#include "hart.hpp"

namespace sim {

class Hart;

using instr_t = uint32_t;

// enum class InstrType : uint8_t { R, I, S, B, U, J };

enum InstrId {
    // R - rype
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    ADDW,
    SLLW,
    SRLW,
    SUBW,
    SRAW,

    // I - type
    JALR,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    LWU,
    LD,
    SLLI,
    SRLI,
    SRAI,
    ADDIW,
    SLLIW,
    SRLIW,
    SRAIW,

    // S - type
    SB,
    SH,
    SW,
    SD,

    // B - type
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,

    // U - type
    LUI,
    AUIPC,

    // J - type
    JAL,

    ECALL,

    FAKE_BB_END,
    NO_ID,
};

constexpr std::array<std::string_view, 52> InstrName{{
    // R - rype
    "ADD",
    "SUB",
    "SLL",
    "SLT",
    "SLTU",
    "XOR",
    "SRL",
    "SRA",
    "OR",
    "AND",
    "ADDW",
    "SLLW",
    "SRLW",
    "SUBW",
    "SRAW",

    // I - type
    "JALR",
    "LB",
    "LH",
    "LW",
    "LBU",
    "LHU",
    "ADDI",
    "SLTI",
    "SLTIU",
    "XORI",
    "ORI",
    "ANDI",
    "LWU",
    "LD",
    "SLLI",
    "SRLI",
    "SRAI",
    "ADDIW",
    "SLLIW",
    "SRLIW",
    "SRAIW",

    // S - type
    "SB",
    "SH",
    "SW",
    "SD",

    // B - type
    "BEQ",
    "BNE",
    "BLT",
    "BGE",
    "BLTU",
    "BGEU",

    // U - type
    "LUI",
    "AUIPC",

    // J - type
    "JAL",

    "ECALL",

    "FAKE_BB_END",
    "NO_ID",
}};

struct EncInstr;

typedef std::function<void(Hart &, const EncInstr *, size_t)> executorT;

struct EncInstr {
    InstrId id;

    uint8_t rd = 0;
    uint8_t rs1 = 0;
    uint8_t rs2 = 0;

    uint64_t imm = 0;

    executorT execute;

    std::string format() {
        std::ostringstream oss{};
        oss << "Instruction: rd: " << +rd << " rs1: " << +rs1 << " rs2: " << +rs2 << " imm: " << imm
            << " (" << static_cast<int64_t>(imm) << ")";
        return oss.str();
    }

    void flush() {
        id = NO_ID;

        rd = 0;
        rs1 = 0;
        rs2 = 0;

        imm = 0;
    }

    bool is_terminal() {
        switch (id) {
            case JAL:
            case JALR:
            case BEQ:
            case BNE:
            case BLT:
            case BGE:
            case BLTU:
            case BGEU:
                return true;
            default:
                return false;
        }
    }

    void decodeRawR(InstrId id_, instr_t raw_instr, executorT exec) {
        execute = exec;
        id = id_;
        rs2 = bits<24, 20>(raw_instr);
        rs1 = bits<19, 15>(raw_instr);
        rd = bits<11, 7>(raw_instr);
    }

    void decodeRawI(InstrId id_, instr_t raw_instr, executorT exec) {
        execute = exec;
        id = id_;
        imm = sbits<31, 20>(raw_instr);
        rs1 = bits<19, 15>(raw_instr);
        rd = bits<11, 7>(raw_instr);

        if (id == InstrId::SRAI) {
            if (bit<10>(imm)) {
                id = InstrId::SRAIW;
            } else {
                id = InstrId::SRLIW;
            }
        }
    }

    void decodeRawB(InstrId id_, instr_t raw_instr, executorT exec) {
        execute = exec;
        id = id_;
        imm = sbits<12, 0>((bit<31>(raw_instr) << 12) | (bits<30, 25>(raw_instr) << 5) |
                           (bits<11, 8>(raw_instr) << 1) | (bit<7>(raw_instr) << 11));
        rs2 = bits<24, 20>(raw_instr);
        rs1 = bits<19, 15>(raw_instr);
    }

    void decodeRawS(InstrId id_, instr_t raw_instr, executorT exec) {
        execute = exec;
        id = id_;
        imm = (sbits<31, 25>(raw_instr) << 5) | (bits<11, 7>(raw_instr));
        rs2 = bits<24, 20>(raw_instr);
        rs1 = bits<19, 15>(raw_instr);
    }

    void decodeRawU(InstrId id_, instr_t raw_instr, executorT exec) {
        execute = exec;
        id = id_;
        imm = sbits<31, 12>(raw_instr) << 12;
        rd = bits<11, 7>(raw_instr);
    }

    void decodeRawJ(InstrId id_, instr_t raw_instr, executorT exec) {
        execute = exec;
        id = id_;
        imm = sbits<20, 0>((bit<31>(raw_instr) << 20) | (bits<30, 21>(raw_instr) << 1) |
                                 (bit<20>(raw_instr) << 11) | (bits<19, 12>(raw_instr) << 12));
        rd = bits<11, 7>(raw_instr);
    }

};

} // sim