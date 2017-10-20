cmake_minimum_required(VERSION 3.5)
project(HUB75)

set(STM32CUBEF4_URL "http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stm32cubef4.zip")
set(STM32CUBEF4_FILE "${CMAKE_BINARY_DIR}/stm32cubef4.zip")
set(STM32CUBEF4_FOLDER "${CMAKE_BINARY_DIR}/STM32Cube_FW_F4_V1.16.0")

if (NOT EXISTS "${STM32CUBEF4_FILE}")
    message(STATUS "Downloading STM32CubeF4...")
    file(
        DOWNLOAD "${STM32CUBEF4_URL}" "${STM32CUBEF4_FILE}"
        EXPECTED_HASH SHA256=fb3efae16815f6ed8931eaa9bd16b0a74b3c4179c5b9acd30f5570bbf0806361
    )
    message(STATUS "Download complete.")
endif ()

if(NOT EXISTS "${STM32CUBEF4_FOLDER}")
    message(STATUS "Extracting STM32CubeF4...")
    execute_process(
        COMMAND "unzip" "${STM32CUBEF4_FILE}" "STM32Cube_FW_F4_V1.16.0/Drivers/CMSIS/*" "STM32Cube_FW_F4_V1.16.0/Drivers/STM32F4xx_HAL_Driver/*" "STM32Cube_FW_F4_V1.16.0/Projects/STM32F4-Discovery/Templates/TrueSTUDIO/STM32F4-Discovery/STM32F407VG_FLASH.ld"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
    execute_process(
        COMMAND "find" "." "-type" "f" "-name" "*template.c" "-exec" "rm" "{}" "+"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
    message(STATUS "Extracting complete.")
endif()

enable_language(ASM)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)

set(CMAKE_CXX_STANDARD 14)

file(GLOB RECURSE LINKER_SCRIPT "STM32F407VG_FLASH.ld")

set(CUSTOM_COMPILER_FLAGS "-mcpu=cortex-m4 -mthumb -DSTM32F407xx -Wall -flto")
set(CUSTOM_LINKER_FLAGS "-mcpu=cortex-m4 -mthumb -Og -flto -ffunction-sections -fdata-sections -fno-move-loop-invariants -Xlinker --gc-sections --specs=nosys.specs -T${STM32CUBEF4_FOLDER}/Projects/STM32F4-Discovery/Templates/TrueSTUDIO/STM32F4-Discovery/STM32F407VG_FLASH.ld")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUSTOM_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILER_FLAGS} -fconcepts")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINKER_FLAGS}")

file(GLOB_RECURSE SOURCES
    Src/*.c
    Src/*.cpp
    ${STM32CUBEF4_FOLDER}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
    ${STM32CUBEF4_FOLDER}/Drivers/STM32F4xx_HAL_Driver/*.c
)

include_directories(
    Inc
    ${STM32CUBEF4_FOLDER}/Drivers/CMSIS/Include
    ${STM32CUBEF4_FOLDER}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32CUBEF4_FOLDER}/Drivers/STM32F4xx_HAL_Driver/Inc
)

add_executable(hub75 ${SOURCES})
