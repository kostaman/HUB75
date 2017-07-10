cmake_minimum_required(VERSION 3.5)
project(HUB75)

enable_language(ASM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_CXX_STANDARD 14)

set(CUSTOM_COMPILER_FLAGS "-mcpu=cortex-m4 -mthumb -DSTM32F407xx -Wall")
set(CUSTOM_LINKER_FLAGS "-mcpu=cortex-m4 -mthumb -Og -ffunction-sections -fdata-sections -fno-move-loop-invariants -Xlinker --gc-sections --specs=nosys.specs -TSTM32F407VGTx_FLASH.ld")

set(CMAKE_ASM_FLAGS_RELEASE "")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUSTOM_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILER_FLAGS} -fconcepts")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINKER_FLAGS}")

file(GLOB_RECURSE SOURCES Src/*.c Src/*.cpp startup/*.s Drivers/**/*.c)

configure_file(STM32F407VGTx_FLASH.ld STM32F407VGTx_FLASH.ld)

include_directories(
        Inc
        Drivers/CMSIS/Include
        Drivers/CMSIS/Device/ST/STM32F4xx/Include
        Drivers/STM32F4xx_HAL_Driver/Inc
)

add_executable(hub75 ${SOURCES})