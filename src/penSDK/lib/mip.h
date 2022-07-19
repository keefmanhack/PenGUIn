#ifndef MIP_H_
#define MIP_H_

#include <assert.h>
#include "../color.h"

typedef struct {
    int width;
    int height;
    int x0;
    int y0;
    Color  color;
    // Bip* children[];
} Mip_t;

void Mip_create(Mip_t * const this, int w, int h, int x0, int y0, Color c);
void Mip_render(Mip_t * const this);

#endif



