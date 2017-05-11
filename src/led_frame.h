#ifndef HUB75_LED_FRAME_H
#define HUB75_LED_FRAME_H

#include <cstddef>
#include <array>
#include <bitset>

namespace HUB75 {

    template<size_t Columns, size_t Rows>
    class LedFrame {

        std::bitset<Columns * Rows> pixels;

    public:

        bool pixel(size_t col, size_t row) {
            return pixels[col + row * Columns];
        }

        void pixel(size_t col, size_t row, bool value) {
            pixels[col + row * Columns] = value;
        }

    };
}

#endif //HUB75_LED_FRAME_H
