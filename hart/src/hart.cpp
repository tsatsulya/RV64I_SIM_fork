#include "hart.hpp"

#include <exception>
#include <ranges>
#include <sstream>

#include "elfio/elfio.hpp"

namespace sim {

std::string Hart::format_registers() {
    std::ostringstream oss{};
    for (size_t i = 0; i < m_regfile.size(); ++i) {
        oss << "\nregister[" << i << "] = " << std::dec << m_regfile[i];
    }
    return oss.str();
}

void Hart::load_elf_file(std::string &elf_file) {
    ELFIO::elfio reader;
    reader.load(elf_file);

    if (reader.get_class() != ELFIO::ELFCLASS64) {
        throw std::runtime_error{"Elf file class doesn't match with ELFCLASS64"};
    }

    auto is_segment_loadable = [](const auto &segment) {
        return segment->get_type() == ELFIO::PT_LOAD;
    };

    for (auto &segment : reader.segments | std::views::filter(is_segment_loadable)) {
        m_mem.store(segment->get_virtual_address(), segment->get_data(),
                    segment->get_memory_size());
    }

    auto start_pc = reader.get_entry();
    m_pc = start_pc;
    m_pc_next = start_pc + 4;

    set_reg(2, 0x90000);
}

uint64_t Hart::get_pc() const noexcept { return m_pc; }

uint64_t Hart::get_pc_next() const noexcept { return m_pc_next; }

reg_t Hart::get_reg(reg_id_t reg_id) const { return m_regfile[reg_id]; }

void Hart::set_pc(addr_t pc) noexcept { m_pc = pc; }

void Hart::set_next_pc(addr_t pc_next) noexcept { m_pc_next = pc_next; }

void Hart::set_reg(reg_id_t reg_id, reg_t value) {
    m_regfile[reg_id] = value;
    m_regfile[0] = 0;
};

}  // namespace sim
