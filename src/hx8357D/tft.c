#include <string.h>

#include "tft.h"
#include "commands.h"
#include "nrf52840_util.h"

static void TFT_writecommand(uint8_t command){
    config_dport_out();
	UNSET_CS;
	
	UNSET_DCX;

	SET_RDX; 

	// clear parralel port first
    NRF_P1->OUT &= ~DPORT_MASK;

	// send command
	NRF_P1->OUT |= ((int)command) << PAR_PIN_START;

	UNSET_WRX; 

	SET_WRX;
}

static void TFT_writedata(uint8_t d){
    config_dport_out();
	UNSET_CS;
	SET_RDX;
	SET_DCX;
    // clear parralel port first
    NRF_P1->OUT &= ~DPORT_MASK;
	NRF_P1->OUT |= (d & 0xFF) << PAR_PIN_START;


    // printk("Data port: %d\n", NRF_P1->OUT >> PAR_PIN_START & 0xFF);
	UNSET_WRX;
	SET_WRX;

}

static void TFT_readdata(void){
    config_dport_in();
	UNSET_CS;
	SET_DCX;

	SET_WRX;
	
	//  perform dummy read
	//  write rdx low
	UNSET_RDX;
	delay();
	//  write rdx high
	SET_RDX;
	//  end dummy read


	int data;
	data = NRF_GPIO->IN;

	printk("Read Data: %d\n", (NRF_P1->IN >> PAR_PIN_START & 0xff));
	data =0;
	// read three bytes
	for(int i =0; i< 3; i++){
		UNSET_RDX;
		delay();
		//write rdx high
		SET_RDX;

		delay();

		printk("Read Data: %d\n", (NRF_P1->IN >> PAR_PIN_START & 0xff));

		
	}
	printk("Read Data: %d\n", data);

}

static void TFT_setAddrWindow(int x0, int y0, int x1, int y1){
    UNSET_CS;

    TFT_writecommand(PASET);
    TFT_writedata(x0>>8);
    TFT_writedata(x0);
    TFT_writedata(x1>>8);
    TFT_writedata(x1);

    TFT_writecommand(CASET);
    TFT_writedata(y0>>8);
    TFT_writedata(y0);
    TFT_writedata(y1>>8);
    TFT_writedata(y1);

    SET_CS;
}

void TFT_reset(void){
    config_data_pins();
	config_dport_out();

	SET_CS;
	SET_WRX;
	SET_RDX;

	UNSET_CS;
	UNSET_DCX;
	TFT_writedata(0);
	TFT_writedata(0);
	TFT_writedata(0);
	UNSET_CS;
}

void TFT_begin(void){
    static const uint8_t init_sequ[] = {
		SWRESET,
		0,
		SETC,
		3,
		0xFF,
		0x83,
		0x57,
		TFTLCD_DELAY,
		250,
		SETRGB,
		4,
		0x00,
		0x00,
		0x06,
		0x06,
		SETCOM,
		1,
		0x25, // -1.52V
		SETOSC,
		1,
		0x68, // Normal mode 70Hz, Idle mode 55 Hz
		SETPANEL,
		1,
		0x05, // BGR, Gate direction swapped
		SETPWR1,
		6,
		0x00,
		0x15,
		0x1C,
		0x1C,
		0x83,
		0xAA,
		SETSTBA,
		6,
		0x50,
		0x50,
		0x01,
		0x3C,
		0x1E,
		0x08,
		// MEME GAMMA HERE
		SETCYC,
		7,
		0x02,
		0x40,
		0x00,
		0x2A,
		0x2A,
		0x0D,
		0x78,
		COLMOD,
		1,
		0x55,
		MADCTL,
		1,
		0xC0,
		TEON,
		1,
		0x00,
		TEARLINE,
		2,
		0x00,
		0x02,
		SLPOUT,
		0,
		TFTLCD_DELAY,
		150,
		DISPON,
		0,
		TFTLCD_DELAY,
		50
    };

    TFT_reset();
    delay();

    UNSET_CS;
    int i = 0;
	while (i < sizeof(init_sequ)) {
      uint8_t r = init_sequ[i++];
      uint8_t len = init_sequ[i++];
      if (r == TFTLCD_DELAY) {
        delay();
		delay();
      } else {

        UNSET_CS;
        TFT_writecommand(r);
        for (uint8_t d = 0; d < len; d++) {
          uint8_t x = init_sequ[i++];
          TFT_writedata(x);
        }
        SET_CS;
      }
    }


	delay();
}

// void TFT_render(Mip_t * const b){
// 	TFT_setAddrWindow(b->x0, b->y0, b->x0 + b->width, b->y0 + b->height);

// 	TFT_writecommand(RAMWR);
	
// 	int len  = b->width * b->height;
// 	while(len){
// 		TFT_writedata(b->color);
// 		TFT_writedata(b->color>>8);
// 		len--;
// 	}
// }

void TFT_renderPixel(int x, int y, Color c){
	TFT_setAddrWindow(x, y, x+1, y+1);

	TFT_writecommand(RAMWR);

	TFT_writedata(c);
	TFT_writedata(c>>8);
}