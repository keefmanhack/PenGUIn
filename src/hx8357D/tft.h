#include <stdint.h>
#include <sys/printk.h>
#include <zephyr.h>
#include "../lib/mip.h"
#include "../color.h"

void TFT_reset(void);
void TFT_begin(void);
void TFT_renderPixel(int x, int y, Color c);
