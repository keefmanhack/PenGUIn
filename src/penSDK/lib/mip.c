#include "mip.h"
#include "../hx8357D/tft.h"

void Mip_create(Mip_t * const this, int w, int h, int x0, int y0, Color c){
    this->height = h;
    this->width = w;
    this->x0 = x0;
    this->y0 = y0;
    this->color = c;
}

void Mip_render(Mip_t * const this){
    if(this==NULL){
        assert(0);
        return;
    }

    TFT_render(this);
}