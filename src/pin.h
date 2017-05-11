#ifndef HUB75_PIN_H
#define HUB75_PIN_H

#include <stm32f4xx_hal.h>

namespace HUB75 {

    template<unsigned int GpioPort, uint16_t GpioPin>
    struct Pin {

        static void high() {
            HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef *>(GpioPort), GpioPin, GPIO_PIN_SET);
        }

        static void low() {
            HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef *>(GpioPort), GpioPin, GPIO_PIN_RESET);
        }
    };
}

#endif //HUB75_PIN_H
