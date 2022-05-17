typedef struct {
    int x;
    int y;
} pos_xy_t;

void RES4WIRE_enable(void);
void RES4WIRE_unenable(void);
pos_xy_t RES4WIRE_getLastPos(void);