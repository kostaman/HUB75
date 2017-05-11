#ifndef HUB75_HUB75_H
#define HUB75_HUB75_H

#include <cstddef>
#include "pin.h"
#include "pin_row.h"
#include "frame.h"
#include "led_frame.h"

namespace HUB75 {

    template<
            size_t Columns, size_t Rows,
            class dataPinRow,
            class rowSelectPinRow,
            class clkPin,
            class latPin,
            class oePin
    >
    class HUB75 {

        static constexpr size_t ScanLimit = Rows / 2;

    public:

        HUB75() {
        }

        template<class PixelType>
        void display(Frame<Columns, Rows, PixelType> &frame) {
            LedFrame<3 * Columns, Rows> ledFrame;
            for (size_t framePosition = 0; framePosition < PixelType::FrameCount; framePosition++) {
                frame.populateLedFrame(ledFrame, framePosition);
                display(ledFrame);
            }
        }

    private:

        void display(LedFrame<3 * Columns, Rows> &ledFrame) {
            rowSelectPinRow::set(0);
            uint8_t dataValue = 0;

            auto setBit = [&dataValue](uint8_t pos, bool value) {
                dataValue |= static_cast<int>(value) << pos;
            };

            oePin::low();

            for (size_t scan = 0; scan < ScanLimit; scan++) {
                rowSelectPinRow::set(scan);
                latPin::low();

                for (size_t col = 0; col < Columns; col++) {
                    dataValue = 0;
                    // Upper row
                    setBit(0, ledFrame.pixel(3 * col + 0, scan));
                    setBit(1, ledFrame.pixel(3 * col + 1, scan));
                    setBit(2, ledFrame.pixel(3 * col + 2, scan));

                    // Lower row
                    setBit(3, ledFrame.pixel(3 * col + 0, scan + ScanLimit));
                    setBit(4, ledFrame.pixel(3 * col + 1, scan + ScanLimit));
                    setBit(5, ledFrame.pixel(3 * col + 2, scan + ScanLimit));

                    clkPin::low();
                    dataPinRow::set(dataValue);
                    clkPin::high();
                    clkPin::low();
                }

                latPin::high();
            }

            oePin::high();
        }

    };

}

#endif //HUB75_HUB75_H
