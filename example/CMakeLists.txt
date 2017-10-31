cmake_minimum_required(VERSION 3.8)
project(HUB75)

set(CUBEF4_URL "http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stm32cubef4.zip")
set(CUBEF4_FILE "${CMAKE_BINARY_DIR}/stm32cubef4.zip")
set(CUBEF4_DIR_NAME "STM32Cube_FW_F4_V1.17.0")
set(CUBEF4_DIR "${CMAKE_BINARY_DIR}/${CUBEF4_DIR_NAME}")

if (NOT EXISTS "${CUBEF4_FILE}")
    message(STATUS "Downloading STM32CubeF4...")
    file(
        DOWNLOAD "${CUBEF4_URL}" "${CUBEF4_FILE}"
        EXPECTED_HASH SHA384=b6394f3c936c9f7ee42ba74ef96ee0a8ad2ebe32aea68a22f7e4874d23d4e9931865d2402b2222c8a26524eab11c9564
    )
    message(STATUS "Download complete.")
endif ()

if(NOT EXISTS "${CUBEF4_DIR}")
    message(STATUS "Extracting STM32CubeF4...")
    execute_process(
        COMMAND "unzip" "${CUBEF4_FILE}" "${CUBEF4_DIR_NAME}/Drivers/CMSIS/*" "${CUBEF4_DIR_NAME}/Drivers/STM32F4xx_HAL_Driver/*" "${CUBEF4_DIR_NAME}/Projects/STM32F4-Discovery/Templates/SW4STM32/STM32F4-Discovery/STM32F407VGTx_FLASH.ld"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
    execute_process(
        COMMAND "find" "." "-type" "f" "-name" "*template.c" "-exec" "rm" "{}" "+"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    )
    message(STATUS "Extracting complete.")
endif()

enable_language(ASM)

set(CMAKE_CXX_STANDARD 17)

set(CUSTOM_COMPILER_FLAGS "-mcpu=cortex-m4 -mthumb -O3 -flto -DSTM32F407xx -Wall")
set(CUSTOM_LINKER_FLAGS "-mcpu=cortex-m4 -mthumb -O3 -flto -ffunction-sections -fdata-sections -fno-move-loop-invariants -Xlinker --gc-sections -T${CUBEF4_DIR}/Projects/STM32F4-Discovery/Templates/SW4STM32/STM32F4-Discovery/STM32F407VGTx_FLASH.ld")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUSTOM_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILER_FLAGS} -fconcepts")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUSTOM_LINKER_FLAGS}")

file(GLOB_RECURSE SOURCES
    Src/*.c
    Src/*.cpp
    ${CUBEF4_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.s
    ${CUBEF4_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c
    ${CUBEF4_DIR}/Drivers/STM32F4xx_HAL_Driver/*.c
)

include_directories(
    Inc
    ${CUBEF4_DIR}/Drivers/CMSIS/Include
    ${CUBEF4_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${CUBEF4_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
)

add_executable(${PROJECT_NAME}.elf ${SOURCES})
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD COMMAND arm-none-eabi-size "${PROJECT_NAME}.elf")