#include "mip.h"
#include "../color.h"
#include "../fonts/font.h"

typedef enum {
    SMALL,
    MEDIUM,
    LARGE,

    MAX_TEXTSIZES
} TEXTSIZE;

typedef struct {
    Mip_t super;
    const char * str;
    const Font_t * font;
}Text_t;

void Text_create(Text_t * const this, int x0, int y0, Color c, const char * str, const Font_t * font);
void Text_render(Text_t * const this);