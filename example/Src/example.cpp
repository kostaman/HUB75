#include "stm32f4xx_hal.h"
#include "../Drivers/HUB75/hub75.h"

extern "C"
void display() {

    using PixelType = HUB75::Pixel8bit;

    HUB75::HUB75<
            128, 64,
            HUB75::PinRow<GPIOC_BASE, 0, 6>,
            HUB75::PinRow<GPIOC_BASE, 6, 5>,
            HUB75::Pin<GPIOC_BASE, GPIO_PIN_11>,
            HUB75::Pin<GPIOC_BASE, GPIO_PIN_12>,
            HUB75::Pin<GPIOC_BASE, GPIO_PIN_13>
    > hub75;

    HUB75::Frame<128, 64, PixelType> frame;

    PixelType red(0xff, 0x00, 0x00);
    PixelType green(0x00, 0xff, 0x00);
    PixelType blue(0x00, 0x00, 0xff);

    auto show = [&](PixelType pixel) {
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