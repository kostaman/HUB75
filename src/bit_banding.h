#ifndef PROJECT_BIT_BANDING_H
#define PROJECT_BIT_BANDING_H

#include "stm32f4xx_hal.h"

template<typename T, typename U>
constexpr size_t offsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

constexpr int bit_band_addr(int base, int bit_band_base, int ptr, int bit) {
    return bit_band_base + (ptr - base) * 32 + bit * 4;
}

constexpr int bit_band_sram(int ptr, int bit) {
    return bit_band_addr(SRAM1_BASE, 0x22000000, ptr, bit);
}

constexpr int bit_band_periph(int ptr, int bit) {
    return bit_band_addr(PERIPH_BASE, 0x42000000, ptr, bit);
}

#endif //PROJECT_BIT_BANDING_H
