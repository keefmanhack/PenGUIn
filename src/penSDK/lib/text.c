#include <string.h>

#include "text.h"
#include "../../hx8357D/def_font.h"
#include "../../hx8357D/tft.h"

void Text_create(Text_t * const this, int x0, int y0, Color c, const char * str, const Font_t * font){
    //  TODO: Adjust the 0 width and height set as placeholders right now
    Mip_create(&(this->super), 0, 0, x0, y0, c);

    this->str = str;
    this->font = font;
}

void Text_render(Text_t * const this){
    int charI, xI, yI, nibCt=0, rightShift =0;
    uint8_t val_4bit;
    Color scaled_color;
    glpyh_desc_t gd;

    int bit =1;


    for(charI=0; charI<strlen(this->str); charI++){
        gd = this->font->glyph_desc[this->str[charI] - FONT_OFFSET];
        for(yI=0; yI<gd.box_h; yI++){
            for(xI=0; xI<gd.box_w; xI++){
                //  Each pixel is encoded with 4 bits.  Loop through and get each nible.  
                //  First get byte of data
                //  Shift right by a nible to read first four bits
                //  2nd time through loop nibCt = 0 so we will read next set of four bits in the 1st byte.  We read left to right
                val_4bit = (this->font->bitmap[gd.bitmap_index + (nibCt/2)] >> (4 * bit)) & 0x0F;

                //  This ensures we don't take time writing data to display if all we have is white space (0x0)
                if(val_4bit >10){
                    //  Just do a simple grey scaling of the values.
                    scaled_color = (Color) 0xFFFF/0xF * val_4bit;

                    TFT_renderPixel(
                        this->super.x0 + xI + rightShift + gd.ofs_x,
                        this->super.y0 + yI - gd.ofs_y - gd.box_h + this->font->bottomLine,
                        scaled_color
                    );

                        // 50+x+fd.ofs_x+right_shift, 50+y - fd.ofs_y+24-fd.box_h, (Color) scaled_val);
                }
                nibCt++;
                bit = nibCt %2;
            }
        }
        nibCt = 0;
        rightShift += (gd.adv_w/6);
    }
}

// // #include "../fonts/OpenSans/size-12/bitmap.h"
// // // #include "../fonts/font.h"

// void render_Letter_A_test(void){
//     int x =0 ,y = 0;
//     int bit =1;
//     int i = 0;

//     int val , scaled_val;
//     int right_shift = 0;;

//     char arr[] = "Ho w                     does !";

//     for(int j = 0; j<strlen(arr); j++){
//         char temp = arr[j];
//         glpyh_desc_t fd = glyph_desc[temp-31];
//         for (y=0; y<fd.box_h; y++){
//             for(x=0; x<fd.box_w; x++){
//                 val = (openSans_size12_bitmap[fd.bitmap_index + (i/2)] >> (4*bit)) & 0b1111;
//                 if(val){
//                     scaled_val = 0xFFFF/0b1111 * val;
//                     TFT_renderPixel(50+x+fd.ofs_x+right_shift, 50+y - fd.ofs_y+24-fd.box_h, (Color) scaled_val);

//                 }
                    
            
//                 i++;
//                 bit = i % 2;
//             }
            
//         }
//         i=0;
//         right_shift+=fd.box_w + fd.ofs_x;
//     }

// }