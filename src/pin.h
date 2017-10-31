#ifndef HUB75_PIN_H
#define HUB75_PIN_H

#include <stm32f4xx_hal.h>
#include "memory.h"

namespace HUB75 {

    template<unsigned int GpioPort, uint8_t GpioPin>
    struct Pin {
        static void high() {
            bit_band(GpioPort, &GPIO_TypeDef::ODR, GpioPin) = 1;
        }

        static void low() {
            bit_band(GpioPort, &GPIO_TypeDef::ODR, GpioPin) = 0;
        }
    };
}

#endif //HUB75_PIN_H
