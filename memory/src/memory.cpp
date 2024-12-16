#include "memory.hpp"

#include <assert.h>
#include <stdexcept>

#include "common.hpp"
#include "page_table_entry.hpp"

namespace sim {

size_t getVPN(virtual_address_t virtual_address, size_t level) {
    assert(level < 3 && "Sv39 does not support VPN level higher than 2");

    size_t low_bit = kPageBitSize + level * kVPNBitSize;
    size_t high_bit = low_bit + kVPNBitSize;

    return my_bits(virtual_address, high_bit, low_bit);
}

[[nodiscard]] physical_address_t MMU::translate(virtual_address_t virtual_address) const {
    // check user_mode: S or U

    // 1.
    size_t a = m_satp_addr * kPageSize;
    size_t level = 2;  // Sv39 max level
    pte_t pte_value;

    // 2.
    while (true) {
        physical_address_t pte_addr = a + getVPN(virtual_address, level) * sizeof(pte_t);

        m_phys_memory.load<pte_t>(pte_addr, pte_value);

        PageTableEntry Pte(pte_value);

        // 3.
        bool reserved_bits_is_null = ((Pte.n() | Pte.pbmt() | Pte.reserved() | Pte.rsw()) == 0);
        if ((Pte.valid() == 0) || (Pte.r() == 0 && Pte.w() == 1) || !reserved_bits_is_null) {
            throw std::runtime_error("page fault");
        }

        // 4.
        if (Pte.r() == 1 || Pte.x() == 1) {
            // find leaf PTE
            break;
        }

        if (level == 0) {
            throw std::runtime_error("page fault");
        }

        --level;
        a = Pte.getPPN(level) * kPageSize;
    }

    // 5. checkLeafFlags

    // 6.
    if (level > 0) {
        if (my_bits(pte_value, level - 1, 0) != 0) {
            throw std::runtime_error("page fault");
        }
    }

    // check access and dirty flags

    // create final pte addr from Pte struct

    // m_phys_memory.load()
    // return m_phys_memory.load(pte);
}

}  // namespace sim