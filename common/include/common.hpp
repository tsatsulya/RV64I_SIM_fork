#pragma once
#include <cstddef>
#include <cstdint>

#include <assert.h>

namespace sim {

template <size_t b>
uint64_t bit(uint64_t value) {
    static_assert(b < 64);
    return (value >> b) & 0b1;
}

template <size_t high_bit, size_t low_bit>
uint64_t bits(uint64_t value) {
    static_assert(high_bit < 64);
    static_assert(low_bit <= high_bit);

    return ((uint64_t(1) << (high_bit - low_bit + 1)) - 1) & (value >> low_bit);
}

template <size_t high_bit, size_t low_bit>
uint64_t sbits(uint64_t value) {
    static_assert(high_bit < 64);
    static_assert(low_bit <= high_bit);

    return static_cast<uint64_t>(static_cast<int64_t>(value) << (63 - high_bit) >>
                                 (63 - high_bit + low_bit));
}

template <size_t high_bit>
uint64_t sext(uint64_t value) {  // == sbits<high_bit , 0>
    static_assert(high_bit < 64);

    return static_cast<int64_t>(value) << (63 - high_bit) >> (63 - high_bit);
}

}  // namespace sim
