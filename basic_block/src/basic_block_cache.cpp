#include "basic_block_cache.hpp"

#include <fmt/format.h>

#include "basic_block.hpp"
#include "common.hpp"
#include "common_mem.hpp"
#include "logger.hpp"

namespace sim {
BasicBlock& BasicBlockCache::find(virtual_address_t virtual_address) {
    // Logger &myLogger = Logger::getInstance();

    auto bb_id = bits<kPcCommonBitSize + kBBCacheBitSize, kPcCommonBitSize>(virtual_address);
    // myLogger.message(Logger::severity_level::verbose, "BBCache",
    //                  fmt::format("addr: {:#x}, bb_id: {:b}", virtual_address, bb_id));

    BasicBlock &bb = m_basic_block[bb_id];
    // myLogger.message(Logger::severity_level::verbose, "BBCache",
    //                fmt::format("addr: {:#x}, bb.getVirtualAddress: {:#x}", virtual_address,
    //                            bb.getVirtualAddress()));
    return bb;
}

// void BasicBlockCache::cacheFlush() {
//     for (size_t i = 0; i < kBBCacheSize; ++i) {
//         m_basic_block[i].flushBB();
//     }
// }

}  // namespace sim