#include "tlb.hpp"

#include "common.hpp"

namespace sim {

bool TLB::find(virtual_address_t virtual_address, host_address_ptr_t &host_address_ptr) {
    Entry &entry = m_table[bits<kPageBitSize + kTlbBitSize, kPageBitSize>(virtual_address)];
    host_address_ptr = entry.host_address_ptr + (virtual_address & kPageSizeMask);
    return (virtual_address & ~kPageSizeMask) == entry.virtual_address;
}

void TLB::update(virtual_address_t virtual_address, host_address_ptr_t host_address_ptr) {
    Entry &entry = m_table[bits<kPageBitSize + kTlbBitSize, kPageBitSize>(virtual_address)];

    auto page_offset = virtual_address & kPageSizeMask;

    entry.virtual_address = virtual_address - page_offset;
    entry.host_address_ptr = host_address_ptr - page_offset;
}

void TLB::tableFlush() {
    for (auto &table_elem : m_table) {
        table_elem.virtual_address = 0;
        table_elem.host_address_ptr = nullptr;
    }
}

}  // namespace sim
