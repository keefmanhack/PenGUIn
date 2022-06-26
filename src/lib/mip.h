#ifndef MIP_H_
#define MIP_H_

#include <assert.h>
#include "../color.h"
// #include "../util/list.h"

typedef struct {
    int width;
    int height;
    int x0;
    int y0;
    Color  color;
    // List_t *children;
} Mip_t;

void Mip_create(Mip_t * const this, int w, int h, int x0, int y0, Color c);
void Mip_render(Mip_t * const this);
void Mip_add(Mip_t * const this, Mip_t * const newMip);
void Mip_remove(Mip_t * const this, Mip_t * const rmMip);


#endif



