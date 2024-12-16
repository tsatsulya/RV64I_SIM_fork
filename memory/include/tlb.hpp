#pragma once

#include <cstddef>
#include <cstdint>

#include "common_mem.hpp"

namespace sim {

class TLB final {
   public:
    struct Entry {
        virtual_address_t virtual_address;
        host_address_ptr_t host_address_ptr;
    };

    static constexpr size_t kTlbBitSize = 8;
    static constexpr size_t kTlbEntries = 1 << kTlbBitSize;  // 1 << 8 = 256, 256 * (8 + 8) == 4096

   private:
    Entry m_table[kTlbEntries]{};  // sizeof PAGE = 0x1000

   public:
    bool find(virtual_address_t virtual_address, host_address_ptr_t &host_address_ptr);
    void update(virtual_address_t virtual_address, host_address_ptr_t host_address_ptr);
    void tableFlush();
};

}  // namespace sim
