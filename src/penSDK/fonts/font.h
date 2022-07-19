#include <stdint.h>

#ifndef FONT_H_
#define FONT_H_ 

#define FONT_OFFSET (' ' - 1)


typedef struct {
    int bitmap_index;
    int adv_w;
    int box_w;
    int box_h;
    int ofs_x;
    int ofs_y;
} glpyh_desc_t;

typedef struct {
    const uint8_t *bitmap;
    const glpyh_desc_t *glyph_desc;
    int bottomLine;
    int charCount;
}Font_t;

#endif
