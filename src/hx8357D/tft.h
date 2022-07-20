#include <stdint.h>
#include <sys/printk.h>
#include <zephyr.h>
#include "../penSDK/lib/mip.h"
#include "../penSDK/color.h"

void TFT_reset(void);
void TFT_begin(void);
void TFT_renderPixel(int x, int y, Color c);
void TFT_render(Mip_t * const b);
