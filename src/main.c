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
	setAnalog(0);
	setAnalog(1);
	setAnalog(2);
	setAnalog(3);
	setAnalog(4);
	setAnalog(5);
	setAnalog(6);
	setAnalog(7);
	volatile int myDelay;

	unsetAnalog(3);

	while(1){
		printk("Analog Values: |  0 = %d   |  1 = %d   | 2 = %d   | 3 = %d   | 4 = %d   | 5 = %d   | 6 = %d   | 7 = %d  |\n", 
			readAnalog(0),
			readAnalog(1),
			readAnalog(2),
			readAnalog(3),
			readAnalog(4),
			readAnalog(5),
			readAnalog(6),
			readAnalog(7)
		);

		myDelay=10000000;
		while(myDelay--){}
	}


	// penGUIn_start();

	// Mip_t mip1;
	// Text_t text1;

	// Text_create(&text1, 50, 50, Color_creatRGB(2,255,100), "Sucks", &PERM_MARK_24PT_REG);

	// Mip_create(&mip1, HX8357D_WIDTH, HX8357D_LENGTH, 0,0, Color_creatRGB(0, 0 , 255));

	// Mip_render(&mip1);
	// Text_render(&text1);
}