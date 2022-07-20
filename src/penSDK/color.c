#include "./color.h"
#include "../hx8357D/16bit_color.h"

#define BYTE_LEN 8

Color Color_creatRGB(uint8_t r, uint8_t g, uint8_t b){
   uint16_t red = ((r >> (BYTE_LEN - RED_BIT_LEN) << (RED_BIT_LEN + BLUE_BIT_LEN)));
   uint16_t blue = ((b >> (BYTE_LEN - BLUE_BIT_LEN)) << BLUE_BIT_LEN);
   uint16_t green = (g >> (BYTE_LEN-GREEN_BIT_LEN));

   return (Color) red | blue | green;
}