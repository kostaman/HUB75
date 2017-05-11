#include "stm32f4xx_hal.h"
#include "../Drivers/HUB75/hub75.h"

extern "C"
void display() {

    HUB75::HUB75<
            128, 64,
            HUB75::PinRow<GPIOC_BASE, 0, 6>,
            HUB75::PinRow<GPIOC_BASE, 6, 5>,
            HUB75::Pin<GPIOC_BASE, GPIO_PIN_11>,
            HUB75::Pin<GPIOC_BASE, GPIO_PIN_12>,
            HUB75::Pin<GPIOC_BASE, GPIO_PIN_13>
    > hub75;

    HUB75::Frame<128, 64> frame;

    HUB75::Pixel16bit red(0xff, 0x00, 0x00);
    HUB75::Pixel16bit green(0x00, 0xff, 0x00);
    HUB75::Pixel16bit blue(0x00, 0x00, 0xff);

    auto show = [&](HUB75::Pixel16bit pixel) {
        frame.fill(pixel);
        hub75.display(frame);
        HAL_Delay(500);
    };

    while (true) {
        show(red);
        show(green);
        show(blue);
    }
}