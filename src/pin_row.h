#ifndef HUB75_PIN_ROW_H
#define HUB75_PIN_ROW_H

#include <stm32f4xx_hal.h>

namespace HUB75 {

    template<unsigned int Port, uint8_t Offset, uint8_t Length>
    struct PinRow {

        static void set(uint8_t value) {
            constexpr uint16_t mask = (1 << Length) - 1;
            reinterpret_cast<GPIO_TypeDef *>(Port)->ODR &= ~(mask << Offset);
            reinterpret_cast<GPIO_TypeDef *>(Port)->ODR |= (value & mask) << Offset;
        }

    };

}

#endif //HUB75_PIN_ROW_H
