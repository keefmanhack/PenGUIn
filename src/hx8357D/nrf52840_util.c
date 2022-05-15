#include "nrf52840_util.h"

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

void config_gpio_output(void){
	NRF_P1->PIN_CNF[CS_PIN] = OUTPUT_CONF;

	NRF_P1->PIN_CNF[DCX_PIN] = OUTPUT_CONF;

	NRF_P1->PIN_CNF[WRX_PIN] = OUTPUT_CONF;

	NRF_P1->PIN_CNF[RDX_PIN] = OUTPUT_CONF;
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
