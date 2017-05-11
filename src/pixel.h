#ifndef HUB75_PIXEL_H
#define HUB75_PIXEL_H

#include <cstdint>

namespace HUB75 {

    template<class PixelType>
    constexpr bool checkPixelType() {
        PixelType p;
        PixelType p2(0, 0, 0);
        static_assert(std::is_same<decltype(p.r(0)), void>::value,
                      "PixelType has to have constexpr void r(uint8_t) member function");
        static_assert(std::is_same<decltype(p.g(0)), void>::value,
                      "PixelType has to have constexpr void g(uint8_t) member function");
        static_assert(std::is_same<decltype(p.b(0)), void>::value,
                      "PixelType has to have constexpr void b(uint8_t) member function");
        static_assert(std::is_same<decltype(p.r()), uint8_t>::value,
                      "PixelType has to have constexpr uint8_t r() member function");
        static_assert(std::is_same<decltype(p.g()), uint8_t>::value,
                      "PixelType has to have constexpr uint8_t g() member function");
        static_assert(std::is_same<decltype(p.b()), uint8_t>::value,
                      "PixelType has to have constexpr uint8_t b() member function");
        static_assert(std::is_same<decltype(PixelType::FrameCount), const size_t>::value,
                      "PixelType has to have static const size_t FrameCount member");
        return true;
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
