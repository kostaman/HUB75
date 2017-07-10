#ifndef HUB75_PIXEL_H
#define HUB75_PIXEL_H

#include <cstdint>

namespace HUB75 {

    template <typename T>
    concept bool Pixel(){
        return requires(T p, uint8_t v) {
            { T::FrameCount } -> uint8_t;

            { p.r() } -> uint8_t;
            { p.g() } -> uint8_t;
            { p.b() } -> uint8_t;

            { p.r(v) } -> void;
            { p.g(v) } -> void;
            { p.b(v) } -> void;
        };
    }

    /**
     * 5 bit color depth per channel
     * 0b0BBBBBGGGGGRRRRR
     */
    class Pixel16bit {

        uint16_t value;

        static const uint16_t mask = 0x1F;

    public:

        static const size_t FrameCount = 5;

        constexpr Pixel16bit() : value(0) {
        }

        constexpr Pixel16bit(uint8_t red, uint8_t green, uint8_t blue) : value(0) {
            r(red);
            g(green);
            b(blue);
        }

        constexpr uint8_t r() {
            return value & mask;
        }

        constexpr uint8_t g() {
            return (value >> 5) & mask;
        }

        constexpr uint8_t b() {
            return (value >> 10) & mask;
        }

        constexpr void r(uint8_t v) {
            value &= ~mask;
            value |= v & mask;
        }

        constexpr void g(uint8_t v) {
            value &= ~(mask << 5);
            value |= (v & mask) << 5;
        }

        constexpr void b(uint8_t v) {
            value &= ~(mask << 10);
            value |= (v & mask) << 10;
        }

    };


    /**
     * 2 bit color depth per channel
     * 0b00BBGGRR
     */
    class Pixel8bit {

        uint8_t value;

        static const uint8_t mask = 0x03;

    public:

        static const size_t FrameCount = 2;

        constexpr Pixel8bit() : value(0) {
        }

        constexpr Pixel8bit(uint8_t red, uint8_t green, uint8_t blue) : value(0) {
            r(red);
            g(green);
            b(blue);
        }

        constexpr uint8_t r() {
            return value & mask;
        }

        constexpr uint8_t g() {
            return (value >> 2) & mask;
        }

        constexpr uint8_t b() {
            return (value >> 4) & mask;
        }

        constexpr void r(uint8_t v) {
            value &= ~mask;
            value |= v & mask;
        }

        constexpr void g(uint8_t v) {
            value &= ~(mask << 2);
            value |= (v & mask) << 2;
        }

        constexpr void b(uint8_t v) {
            value &= ~(mask << 4);
            value |= (v & mask) << 4;
        }

    };

}

#endif //HUB75_PIXEL_H
