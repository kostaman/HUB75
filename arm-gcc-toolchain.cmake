include(CMakeForceCompiler)

# Targeting an embedded system, no OS.
set(CMAKE_SYSTEM_NAME Generic)

CMAKE_FORCE_C_COMPILER(arm-none-eabi-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(arm-none-eabi-g++ GNU)

# Find the target environment prefix..
# First see where gcc is keeping libc.a
execute_process(
        COMMAND ${CMAKE_C_COMPILER} -print-file-name=libc.a
        OUTPUT_VARIABLE CMAKE_INSTALL_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Strip the filename off
get_filename_component(CMAKE_INSTALL_PREFIX
        "${CMAKE_INSTALL_PREFIX}" PATH
        )
# Then find the canonical path to the directory one up from there
get_filename_component(CMAKE_INSTALL_PREFIX
        "${CMAKE_INSTALL_PREFIX}/.." REALPATH
        )
set(CMAKE_INSTALL_PREFIX  ${CMAKE_INSTALL_PREFIX} CACHE FILEPATH
        "Install path prefix, prepended onto install directories.")

message(STATUS "Cross-compiling with the gcc-arm-embedded toolchain")
message(STATUS "Toolchain prefix: ${CMAKE_INSTALL_PREFIX}")

set(CMAKE_FIND_ROOT_PATH  ${CMAKE_INSTALL_PREFIX})

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_FLAGS "-fno-common -ffunction-sections -fdata-sections")

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m4")

    set(CMAKE_C_FLAGS
            "${CMAKE_C_FLAGS}"
            "-mcpu=cortex-m4 -march=armv7e-m -mthumb"
            "-mfloat-abi=hard -mfpu=fpv4-sp-d16"
            )

elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-m3")

    set(CMAKE_C_FLAGS
            "${CMAKE_C_FLAGS}"
            "-mcpu=cortex-m3 -march=armv7-m -mthumb"
            "-msoft-float"
            )

elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "cortex-a9")

    set(CMAKE_C_FLAGS
            "${CMAKE_C_FLAGS}"
            "-mcpu=cortex-a9 -march=armv7-a -mthumb"
            "-mfloat-abi=hard -mfpu=neon"
            )

else ()
    message(WARNING
            "Processor not recognised in toolchain file, "
            "compiler flags not configured."
            )
endif ()

# When we break up long strings in CMake we get semicolon
# separated lists, undo this here...
string(REGEX REPLACE ";" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")

set(BUILD_SHARED_LIBS OFF)
