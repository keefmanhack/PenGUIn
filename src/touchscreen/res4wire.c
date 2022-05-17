#include "res4wire.h"

static pos_xy_t this_val;

void RES4WIRE_enable(void){

}

void RES4WIRE_unenable(void){

}

pos_xy_t RES4WIRE_getLastPos(void){
    return this_val;
}