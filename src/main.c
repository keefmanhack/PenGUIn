#include "penGUIn.h"
#include "lib/mip.h"
#include "lib/text.h"
#include "color.h"
#include "hx8357D/nrf52840_util.h"
#include "fonts/OpenSans/reg_24pt.h"
// #include "fonts/PermMarker/reg_24pt.h"
// #include "fonts/Monospace/reg_24pt.h"

#include <nrf.h>
#include "hx8357D/nrf52840_util.h"

void main(void)
{	
	penGUIn_start();
	// PenGUIn_restart();

	Mip_t mip1, mip2;
	Text_t text1;

	Text_create(&text1, 50, 50, Color_creatRGB(2,255,100), "Marek no suck", &OPEN_SANS_24PT_REG);

	Mip_create(&mip1, HX8357D_WIDTH, HX8357D_LENGTH, 0,0, Color_creatRGB(0, 0 , 255));

	Mip_create(&mip2, 100, 100, 0,200, Color_creatRGB(255, 0 , 0));



	Mip_render(&mip1);
	Mip_render(&mip2);
	Text_render(&text1);
}