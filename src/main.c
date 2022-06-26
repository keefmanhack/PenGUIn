#include "penGUIn.h"
#include "lib/mip.h"
#include "lib/text.h"
#include "color.h"
#include "hx8357D/nrf52840_util.h"
// #include "fonts/OpenSans/reg_24pt.h"
// #include "fonts/PermMarker/reg_24pt.h"
// #include "fonts/Monospace/reg_24pt.h"
#include "nrf52840_HAL.h"

#include <nrf.h>
#include <stdint.h>
#include "hx8357D/nrf52840_util.h"



void main(void)
{	
	Mip_t screen = penGUIn_start();

	Mip_t leftBox;

	// Mip_create leftBox;

	Mip_add(&screen, &leftBox);




	Mip_t mip1;
	Text_t text1;

	Text_create(&text1, 50, 50, Color_creatRGB(2,255,100), "Sucks", &PERM_MARK_24PT_REG);

	Mip_create(&mip1, HX8357D_WIDTH, HX8357D_LENGTH, 0,0, Color_creatRGB(0, 0 , 255));

	Mip_render(&mip1);
	Text_render(&text1);
}