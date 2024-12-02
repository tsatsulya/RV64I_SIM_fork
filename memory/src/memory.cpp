#include "memory.hpp"

#include <assert.h>

#include "common.hpp"
#include "page_table_entry.hpp"

namespace sim {

size_t getVPN(virtual_address_t virtual_address, size_t level) {
    assert(level < 3 && "Sv39 does not support VPN level higher than 2");

    size_t low_bit = kPageBitSize + level * kVPNBitSize;
    size_t high_bit = low_bit + kVPNBitSize;

    // return bits<high_bit, low_bit>(virtual_address);
}

// [[nodiscard]] physical_address_t MMU::translate(virtual_address_t virtual_address) const {
//     // check user_mode: S or U

//     // 1.
//     size_t a = m_satp_addr * kPageSize;
//     size_t level = 2;  // Sv39 max level

//     // 2.
//     while (true) {
//         physical_address_t pte_addr = a + getVPN(virtual_address, level) * sizeof(pte_t);

//         // if (auto status = m_phys_memory.load<pte_t>(pte); !status) {
//         //     return nullptr;  // add status
//         // }

//         // 3.
//         if ((pte.v == 0) || (pte.r == 0 && pte.w == 1) || reserved_bits != 0) {
//             return PAGE_FAULT;
//         }

//         // 4.
//         if (pte.r == 1 || pte.x == 1) {
//             // find leaf PTE
//             break;
//         }

//         if (level == 0) {
//             return PAGE_FAULT;
//         }

//         a = pte.ppn * PAGESIZE;
//         --level;
//     }

//     // 5. checkLeafFlags

//     // 6.
//     if (level > 0) {
//         if (pte[i - 1, 0] != 0) {
//             return PAGE_FAULT;
//         }
//     }

//     // check access and dirty flags

//     return m_phys_memory.load(pte);  // + status
// }

}  // namespace sim