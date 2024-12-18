#include "basic_block.hpp"

#include <fmt/format.h>

#include "decoder.hpp"
#include "executor.hpp"
#include "hart.hpp"
#include "instruction.hpp"
#include "logger.hpp"

namespace sim {

bool BasicBlock::update(const Hart &hart) {
    // Logger &myLogger = Logger::getInstance();

    m_size = 0;
    m_virtual_address = hart.get_pc();
    auto current_addr = m_virtual_address;

    while (m_size < kMaxNumberOfInstr - 1) {
        uint64_t instr;
        hart.load<uint32_t>(current_addr, instr);

        EncInstr enc_instr;
        // FIXME: optimize in goto
        Decoder::decode_instruction(instr, enc_instr);

        m_instructions[m_size] = enc_instr;

        // myLogger.message(Logger::severity_level::standard, "BB", enc_instr.format());
        // myLogger.message(Logger::severity_level::standard, "BB",
        //                  fmt::format("bb pc: {:#x}", current_addr));

        ++m_size;
        current_addr += 4;
        if (enc_instr.is_terminal()) {
            return true;
        }
    }

    m_instructions[kMaxNumberOfInstr - 1] = {.id = FAKE_BB_END, .execute = Executor::execute_fake_bb_end};
    ++m_size;

    return true;
}

}  // namespace sim