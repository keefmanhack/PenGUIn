#include "nrf52840_util.h"

#define DATA_PORT 1

void delay(void){
	volatile int i = 1;
	while(i){
		i--;
	}
    
}

void clearParPort(void){
	for(int i = PAR_PIN_START; i<=PAR_PIN_END; i++){
		NRF_P1->OUTCLR = (1UL << i);
	}
}

void remove_config_gpio(uint8_t pin, uint8_t port){
	if(port == 1){
		NRF_P1->PIN_CNF[pin] = 0;
	}else{
		NRF_P0->PIN_CNF[pin] = 0;
	}
	
}

void config_gpio_output(uint8_t pin, uint8_t port){
	if(port == 1){
		NRF_P1->PIN_CNF[pin] = OUTPUT_CONF;
	}else{
		NRF_P0->PIN_CNF[pin] = OUTPUT_CONF;
	}
}

void config_gpio_input(uint8_t pin, uint8_t port){
	if(port  == 1){
		NRF_P1->PIN_CNF[pin] = INPUT_CONF;
	}else{
		NRF_P0->PIN_CNF[pin] = INPUT_CONF;
	}

}

void config_data_pins(void){
	config_gpio_output(CS_PIN, DATA_PORT);
	config_gpio_output(DCX_PIN, DATA_PORT);
	config_gpio_output(WRX_PIN, DATA_PORT);
	config_gpio_output(RDX_PIN, DATA_PORT);
}

void config_dport_out(void){
	for(int i =PAR_PIN_START; i<=PAR_PIN_END; i++){
		NRF_P1->PIN_CNF[i] = OUTPUT_CONF;
	}
}

void config_dport_in(void){
	for(int i =PAR_PIN_START; i<=PAR_PIN_END; i++){
		NRF_P1->PIN_CNF[i] = INPUT_CONF;
	}
}
