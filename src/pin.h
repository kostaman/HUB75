#ifndef HUB75_PIN_H
#define HUB75_PIN_H

#include <stm32f4xx_hal.h>
#include <stm32f407xx.h>
#include "bit_banding.h"

namespace HUB75 {

    template<unsigned int GpioPort, uint8_t GpioPin>
    struct Pin {

        static constexpr int alias = bit_band_periph(GpioPort + offsetOf(&GPIO_TypeDef::ODR), GpioPin);

        static void high() {
            *(int*)alias = 1;
        }

        static void low() {
            *(int*)alias = 0;
        }
    };
}

#endif //HUB75_PIN_H
