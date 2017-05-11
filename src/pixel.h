#ifndef HUB75_PIXEL_H
#define HUB75_PIXEL_H

#include <cstdint>
#include <bitset>

namespace HUB75 {

    /**
     * 5bit color depth per channel
     * 0x0BBBBBGGGGGRRRRR
     */
    class Pixel16bit {

        uint16_t value;

        static const uint16_t mask = 0x1F;

    public:

        static const size_t FrameCount = 5;

        Pixel16bit() : value(0) {
        }

        Pixel16bit(uint8_t red, uint8_t green, uint8_t blue) : value(0) {
            r(red);
            g(green);
            b(blue);
        }

        uint8_t r() {
            return value & mask;
        }

        uint8_t g() {
            return (value >> 5) & mask;
        }

        uint8_t b() {
            return (value >> 10) & mask;
        }

        void r(uint8_t v) {
            value &= ~mask;
            value |= v & mask;
        }

        void g(uint8_t v) {
            value &= ~(mask << 5);
            value |= (v & mask) << 5;
        }

        void b(uint8_t v) {
            value &= ~(mask << 10);
            value |= (v & mask) << 10;
        }

    };

}

#endif //HUB75_PIXEL_H
