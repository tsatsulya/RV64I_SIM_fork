#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <type_traits>

#include "common_mem.hpp"
#include "fmt/format.h"
#include "logger.hpp"

namespace sim {

class Memory {  // PhysMemory
   private:
    size_t m_size;
    uint8_t *m_mem;

    static constexpr size_t default_mem_size = 0x100000;  // 1 GB

   public:
    Memory(size_t size = default_mem_size) : m_size(size) {
        errno = 0;
        void *mmap_result =
            mmap(NULL, m_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (mmap_result == MAP_FAILED) {
            throw std::runtime_error{fmt::format("Can't mmap memory size of {}, errno: {}",
                                                 std::to_string(m_size), std::strerror(errno))};
        }
        m_mem = static_cast<uint8_t *>(mmap_result);

        // Logger &myLogger = Logger::getInstance();
        // myLogger.message(Logger::severity_level::standard, "Memory",
        //                  fmt::format("{} - {}", static_cast<void *>(m_mem),
        //                              static_cast<void *>(m_mem + m_size)));
    }

    template <typename ValType>
    void load(uint64_t addr, uint64_t &value) const {
        static_assert(std::is_integral_v<ValType>);

        size_t addr_page_offset = addr & kPageSizeMask;
        if (addr_page_offset + sizeof(ValType) > kPageSize) {
            std::runtime_error("Misaligned memory load");
        }

        value = *reinterpret_cast<ValType *>(m_mem + addr);
    }

    template <typename ValType>
    void store(uint64_t addr, uint64_t value) {
        static_assert(std::is_integral_v<ValType>);

        size_t addr_page_offset = addr & kPageSizeMask;
        if (addr_page_offset + sizeof(ValType) > kPageSize) {
            std::runtime_error("Misaligned memory store");
        }

        *reinterpret_cast<ValType *>(m_mem + addr) = value;
    }

    void store(size_t mem_offset, const void *src, size_t count) {
        std::memcpy(m_mem + mem_offset, src, count);
    }
};

size_t getVPN(virtual_address_t virtual_address, size_t level);

class MMU final {
   private:
    Memory &m_phys_memory;
    reg_t m_satp_addr = 0x1000;  // FIXME: implement system registers: satp, status
                                 // status register &

   public:
    MMU(Memory &phys_memory) : m_phys_memory(phys_memory) {}

    MMU(const MMU &mmu) = delete;
    MMU &operator=(const MMU &mmu) = delete;

    MMU(MMU &&mmu) = delete;
    MMU &operator=(MMU &&mmu) = delete;

    ~MMU() = default;

    [[nodiscard]] physical_address_t translate(virtual_address_t virtual_address) const;
};

}  // namespace sim
