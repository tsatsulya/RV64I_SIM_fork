#pragma once

#include "common_mem.hpp"
#include "hart.hpp"
#include "instruction.hpp"

namespace sim {
class BasicBlock final {
   private:
    static constexpr size_t kMaxNumberOfInstr = 32;

    size_t m_size = 0;
    virtual_address_t m_virtual_address;
    EncInstr m_instructions[kMaxNumberOfInstr]{};

   public:
    bool update(const Hart &hart);

    virtual_address_t getVirtualAddress() { return m_virtual_address; }

    EncInstr *getInstructions() { return m_instructions; }
    size_t getSize() { return m_size; }

    // void flushBB() {
    //     // for (size_t i = 0; i < kMaxNumberOfInstr; ++i) {
    //     //     m_instructions[i].flush();
    //     // }
    //     m_size = 0;
    //     m_virtual_address = 0;
    // }
};
}  // namespace sim
