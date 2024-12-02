#pragma once

#include <array>
#include <cstdint>
#include <sstream>

#include "memory.hpp"
#include "common.hpp"

namespace sim {

class Hart final {
   private:
    Memory m_mem{};

    addr_t m_pc, m_pc_next;
    std::array<reg_t, g_regfile_size> m_regfile{};

   private:
    void load_elf_file(std::string &elf_file);

   public:
    Hart(std::string &elf_file) { load_elf_file(elf_file); }

    std::string format_registers();

    addr_t get_pc() const noexcept;
    addr_t get_pc_next() const noexcept;
    reg_t get_reg(reg_id_t reg_id) const;

    void set_pc(addr_t pc) noexcept;
    void set_next_pc(addr_t pc_next) noexcept;
    void set_reg(reg_id_t reg_id, reg_t value);

    template <typename ValType>
    void load(uint64_t addr, uint64_t &value) const {
        m_mem.load<ValType>(addr, value);
    }

    template <typename ValType>
    void store(addr_t addr, uint64_t value) {
        m_mem.store<ValType>(addr, value);
    }
};
}  // namespace sim
