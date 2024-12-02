#include <cstddef>
#include <cstdint>

#include "common.hpp"

namespace sim {

using pte_t = uint64_t;

class PageTableEntry final {
   private:
    pte_t m_pte;

    static constexpr size_t kPPNLowBit = 10;
    static constexpr size_t kPPNHighBit = 53;

   public:
    PageTableEntry(pte_t pte) : m_pte(pte) {}

    explicit PageTableEntry(physical_address_t physical_address, uint8_t flags);

    [[nodiscard]] bool valid() const noexcept { return bit<0>(m_pte); }
    [[nodiscard]] bool r() const noexcept { return bit<1>(m_pte); }
    [[nodiscard]] bool w() const noexcept { return bit<2>(m_pte); }
    [[nodiscard]] bool x() const noexcept { return bit<3>(m_pte); }
    [[nodiscard]] bool u() const noexcept { return bit<4>(m_pte); }
    [[nodiscard]] bool g() const noexcept { return bit<5>(m_pte); }
    [[nodiscard]] bool a() const noexcept { return bit<6>(m_pte); }
    [[nodiscard]] bool d() const noexcept { return bit<7>(m_pte); }

    [[nodiscard]] size_t getPPN(size_t level);
};

}  // namespace sim