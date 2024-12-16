#pragma once
#include "basic_block.hpp"
#include "common_mem.hpp"

namespace sim {
class BasicBlockCache final {
   private:
    static constexpr size_t kBBCacheBitSize = 7;
    static constexpr size_t kBBCacheSize = 2 << kBBCacheBitSize;  // 256

    static constexpr size_t kPcCommonBitSize = 2;  // 4 == 0b100
    static constexpr size_t kPcCommonSize = 1 << kPcCommonBitSize;

    BasicBlock m_basic_block[kBBCacheSize]{};  // sizeof(m_basic_block) == 16 = (1 << 4)
                                               // 256 * 16 == 4096
   public:
    BasicBlock& find(virtual_address_t virtual_address);
    void cacheFlush();
};
}  // namespace sim
