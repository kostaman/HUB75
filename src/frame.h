#ifndef HUB75_FRAME_H
#define HUB75_FRAME_H

#include <cstddef>
#include <array>
#include <type_traits>
#include "pixel.h"
#include "led_frame.h"

namespace HUB75 {

    template<size_t Columns, size_t Rows, class PixelType = Pixel16bit>
    class Frame : std::enable_if<checkPixelType<PixelType>()> {

        std::array<PixelType, Columns * Rows> pixels;

    public:

        Frame() {
            fill(PixelType{});
        }

        PixelType &pixel(size_t col, size_t row) {
            return pixels[col + row * Columns];
        }

        void fill(PixelType pixel) {
            std::fill(pixels.begin(), pixels.end(), pixel);
        }

        void populateLedFrame(LedFrame<3 * Columns, Rows> &ledFrame, size_t framePosition) {
            const uint8_t mask = 1 << framePosition;
            for (size_t row = 0; row < Rows; row++) {
                for (size_t col = 0; col < Columns; col++) {
                    auto &p = pixel(col, row);
                    ledFrame.pixel(3 * col + 0, row, p.r() & mask);
                    ledFrame.pixel(3 * col + 1, row, p.g() & mask);
                    ledFrame.pixel(3 * col + 2, row, p.b() & mask);
                }
            }
        }

    };

}

#endif //HUB75_FRAME_H
