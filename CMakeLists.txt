# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hello_world)

include(src/lvgl_master/CMakeLists.txt)
FILE(GLOB_RECURSE app_sources src/*.h src/*.c )
target_sources(app PRIVATE ${app_sources}
    # src/main.c
    # src/penManager/penGUIn.c
    # src/penManager/penGUIN.h
    # src/penSDK/color.c
    # src/penSDK/color.h
    # src/hx8357D/16bit_color.h
    # src/hx8357D/commands.h
    # src/hx8357D/nrf52840_util.h
    # src/hx8357D/nrf52840_util.c
    # src/hx8357D/tft.c
    # src/hx8357D/tft.h
    # src/penSDK/lib/mip.c
    # src/penSDK/lib/mip.h
    # src/penSDK/lib/text.c
    # src/penSDK/lib/text.h
    # src/penSDK/fonts/font.h
    # src/lvgl_master/src/core/lv_obj.h
    # src/lvgl_master/src/core/lv_obj.c
    # src/lvgl_master/src/core/lv_indev.h
    # src/lvgl_master/src/core/lv_indev.c
    # src/lvgl_master/src/core/lv_refr.h
    # src/lvgl_master/src/core/lv_refr.c
    # src/lvgl_master/src/core/lv_group.h
    # src/lvgl_master/src/core/lv_group.c
    # src/lvgl_master/src/core/lv_disp.h
    # src/lvgl_master/src/core/lv_disp.c
    # src/lvgl_master/src/core/lv_theme.h
    # src/lvgl_master/src/core/lv_theme.c
    # src/lvgl_master/src/misc/lv_assert.h
    # src/lvgl_master/src/draw/lv_draw.h
    # src/lvgl_master/src/draw/lv_draw.c
    # src/lvgl_master/src/misc/lv_anim.h
    # src/lvgl_master/src/misc/lv_anim.c
    # src/lvgl_master/src/misc/lv_timer.h
    # src/lvgl_master/src/misc/lv_timer.c
    # src/lvgl_master/src/misc/lv_async.h
    # src/lvgl_master/src/misc/lv_async.c
    # src/lvgl_master/src/misc/lv_fs.h
    # src/lvgl_master/src/misc/lv_fs.c
    # src/lvgl_master/src/misc/lv_math.h
    # src/lvgl_master/src/misc/lv_math.c
    # src/lvgl_master/src/misc/lv_gc.h
    # src/lvgl_master/src/misc/lv_gc.c
    # src/lvgl_master/src/misc/lv_log.h
    # src/lvgl_master/src/misc/lv_log.c

    # src/lvgl_master/lvgl.h
)

#include "lv_obj.h"
#include "lv_indev.h"
#include "lv_refr.h"
#include "lv_group.h"
#include "lv_disp.h"
#include "lv_theme.h"
#include "../misc/lv_assert.h"
#include "../draw/lv_draw.h"
#include "../misc/lv_anim.h"
#include "../misc/lv_timer.h"
#include "../misc/lv_async.h"
#include "../misc/lv_fs.h"
#include "../misc/lv_gc.h"
#include "../misc/lv_math.h"
#include "../misc/lv_log.h"
