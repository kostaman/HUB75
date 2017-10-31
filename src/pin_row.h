#ifndef HUB75_PIN_ROW_H
#define HUB75_PIN_ROW_H

#include <stm32f4xx_hal.h>
#include "memory.h"

namespace HUB75 {

    template<unsigned int GpioPort, uint8_t GpioPin, uint8_t Length>
    struct PinRow {

        static void set(uint8_t value) {
            constexpr uint16_t mask = (1 << Length) - 1;
            memory(GpioPort, &GPIO_TypeDef::ODR) &= ~(mask << GpioPin);
            memory(GpioPort, &GPIO_TypeDef::ODR) |= (value & mask) << GpioPin;
        }

    };

}

#endif //HUB75_PIN_ROW_H
