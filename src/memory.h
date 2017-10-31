#ifndef MEMORY_H
#define MEMORY_H

#include "stm32f4xx_hal.h"

template<typename T, typename U>
constexpr size_t offsetOf(U T::*member) {
    return (char *) &((T *) nullptr->*member) - (char *) nullptr;
}

volatile uint32_t &memory(uint32_t loc) {
    return *reinterpret_cast<uint32_t *>(loc);
}

template<typename T, typename U>
volatile uint32_t &memory(uint32_t loc, U T::*member) {
    return memory(loc + offsetOf(member));
}

volatile uint32_t &bit_band(uint32_t loc, uint8_t bit) {
    uint32_t base = SRAM1_BASE;
    uint32_t bit_band_base = 0x22000000;
    if (loc >= PERIPH_BASE) {
        base = PERIPH_BASE;
        bit_band_base = 0x42000000;
    }
    return memory(bit_band_base + (loc - base) * 32 + bit * 4);
}

template<typename T, typename U>
volatile uint32_t &bit_band(uint32_t loc, U T::*member, uint8_t bit) {
    return bit_band(reinterpret_cast<uint32_t>(&memory(loc, member)), bit);
}

#endif //MEMORY_H
