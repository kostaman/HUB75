[![Build Status](https://travis-ci.org/petoknm/HUB75.svg?branch=master)](
https://travis-ci.org/petoknm/HUB75)
[![CircleCI](https://circleci.com/gh/petoknm/HUB75.svg?style=svg)](
https://circleci.com/gh/petoknm/HUB75)

# HUB75
HUB75 LED Matrix driver for STM32 using HAL.  
Primary development and testing currently performed on two HUB75e 64x64 RGB LED
panels in series.

## Example
Example usage of this library can be found in file [example/Src/example.cpp](
https://github.com/petoknm/HUB75/blob/master/example/Src/example.cpp).

## Terms & Definitions
- `Pixel` := an arbitrary color depth and format pixel value that models the
Pixel concept
- `PinRow` := a row of 6 consequent GPIO pins sharing the same GPIO port
- `LedFrame` := a frame of 1-bit color pixel data to be pushed to the display
directly
- `Frame` := a frame of pixel data using any `Pixel` type to be displayed on
the display

## Prerequisites
\*Requires a compiler that supports C++17 and Concepts TS (`-fconcepts` flag)
- `arm-none-eabi-gcc`
- `cmake`
- `make`

## Building
During build script generation, ST's STM32CubeF4 library will be downloaded and
extracted so please be patient because it's a big download.
```shell
# In-source build
cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-gcc.cmake .
make

# Out-of-source build
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=arm-none-eabi-gcc.cmake ..
make
```
