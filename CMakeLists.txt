# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

target_sources(app PRIVATE 
    src/main.c
    src/penManager/penGUIn.c
    src/penManager/penGUIN.h
    src/penSDK/color.c
    src/penSDK/color.h
    src/hx8357D/16bit_color.h
    src/hx8357D/commands.h
    src/hx8357D/nrf52840_util.h
    src/hx8357D/nrf52840_util.c
    src/hx8357D/tft.c
    src/hx8357D/tft.h
    src/penSDK/lib/mip.c
    src/penSDK/lib/mip.h
    src/penSDK/lib/text.c
    src/penSDK/lib/text.h
    src/penSDK/fonts/font.h
)
