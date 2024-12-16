#include "common_mem.hpp"

uint64_t my_bits(uint64_t value, size_t high_bit, size_t low_bit) {
    assert(high_bit >= low_bit);

    return ((uint64_t(1) << (high_bit - low_bit + 1)) - 1) & (value >> low_bit);
}