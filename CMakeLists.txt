# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE 
    src/main.c
    src/penGUIn.c
    src/penGUIN.h
    src/color.c
    src/color.h
    src/util.h
    src/hx8357D/16bit_color.h
    src/hx8357D/commands.h
    src/hx8357D/nrf52840_util.h
    src/hx8357D/nrf52840_util.c
    src/hx8357D/tft.c
    src/hx8357D/tft.h
    src/lib/mip.c
    src/lib/mip.h
    src/lib/text.c
    src/lib/text.h
    src/fonts/font.h
    src/nrf52840_HAL.h
    src/nrf52840_HAL.c
)
