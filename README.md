# HUB75
HUB75 LED Matrix driver for STM32 using HAL.  
Primary development and testing currently performed on two HUB75e 64x64 RGB LED panels in series.

## Example

Example usage of this library can be found in file [example/Src/example.cpp](https://github.com/petoknm/HUB75/blob/master/example/Src/example.cpp)

## Terms & Definitions

- `Pixel` := an arbitrary color depth and format pixel value that implements the Pixel interface
- `PinRow` := a row of 6 consequent GPIO pins sharing the same GPIO port
- `LedFrame` := a frame of 1-bit color pixel data to be pushed to the display directly
- `Frame` := a frame of pixel data using any `Pixel` type to be displayed on the display

## Pixel Interface

- `static const size_t FrameCount;`
- `void r(uint8_t);`
- `void g(uint8_t);`
- `void b(uint8_t);`
- `uint8_t r();`
- `uint8_t g();`
- `uint8_t b();`

## Prerequisites
- `arm-none-eabi-gcc`
- `cmake`
- `make`

## Building
```shell
cmake .
make
```