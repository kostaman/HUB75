#ifndef HUB75_PIXEL_H
#define HUB75_PIXEL_H

#include <cstdint>

namespace HUB75 {

    template<typename T>
    concept bool Pixel() {
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
     * 565 RGB pixel
     */
    class Pixel16bit {
        uint16_t value;

    public:
        static const uint8_t FrameCount = 6;

        constexpr Pixel16bit() : value(0) {}

        constexpr Pixel16bit(uint8_t _r, uint8_t _g, uint8_t _b) : value(0) {
            r(_r);
            g(_g);
            b(_b);
        }

        constexpr uint8_t r() {
            return value & 0x1F;
        }

        constexpr uint8_t g() {
            return (value >> 5) & 0x3F;
        }

        constexpr uint8_t b() {
            return (value >> 11) & 0x1F;
        }

        constexpr void r(uint8_t v) {
            value &= ~0x1F;
            value |= (v & 0x1F);
        }

        constexpr void g(uint8_t v) {
            value &= ~(0x3F << 5);
            value |= (v & 0x3F) << 5;
        }

        constexpr void b(uint8_t v) {
            value &= ~(0x1F << 11);
            value |= (v & 0x1F) << 11;
        }
    };

    /**
     * 233 RGB pixel
     */
    class Pixel8bit {
        uint8_t _r : 2;
        uint8_t _g : 3;
        uint8_t _b : 3;

    public:
        static const uint8_t FrameCount = 3;

        constexpr Pixel8bit() : _r(0), _g(0), _b(0) {}

        constexpr Pixel8bit(uint8_t r, uint8_t g, uint8_t b) : _r(r), _g(g), _b(b) {}

        constexpr uint8_t r() {
            return _r;
        }

        constexpr uint8_t g() {
            return _g;
        }

        constexpr uint8_t b() {
            return _b;
        }

        constexpr void r(uint8_t v) {
            _r = v;
        }

        constexpr void g(uint8_t v) {
            _g = v;
        }

        constexpr void b(uint8_t v) {
            _b = v;
        }
    };

}

#endif //HUB75_PIXEL_H
