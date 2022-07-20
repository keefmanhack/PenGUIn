#include "penGUIn.h"
#include "../hx8357D/tft.h"

void penGUIn_start(void){
    TFT_reset();
    TFT_begin();
}

void penGUIn_prev(void){
    //  push state back to previous

    // render
}

void penGUIn_next(void){
    //  push state forward

    // render

}

void penGUIn_update(const Mip_t * const elem){
    //  update state

    //  render screen

}