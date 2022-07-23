//  belongs in header file
typedef struct tchscrn_pnt_t{
    int x;
    int y;
} tchscrn_pnt_t;

bool TchScrn_isPressed(void);
void TchScrn_getPoint(tchscrn_pnt_t * point_p);