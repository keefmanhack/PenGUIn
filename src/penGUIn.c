#include "penGUIn.h"

#include "hx8357D/tft.h"
#include "hx8357D/nrf52840_util.h"
#include "color.h"

Mip_t penGUIn_start(void){
    Mip_t screen;

    TFT_reset();
    TFT_begin();

    Mip_create(&screen, HX8357D_WIDTH, HX8357D_LENGTH, 0,0, WHITE);
    
    return screen;
}