#include <nrf.h>

#define HX8357D_WIDTH   479
#define HX8357D_LENGTH  319

#define CS_PIN 7 // port 1
#define DCX_PIN 6
#define WRX_PIN 5
#define RDX_PIN 4
#define TEST_PIN 0

#define PAR_PIN_START 8
#define PAR_PIN_END   15
#define DPORT_MASK    (0xFFUL << PAR_PIN_START)

#define OUTPUT_CONF (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) | \
					(GPIO_PIN_CNF_DRIVE_S0H1 << GPIO_PIN_CNF_DRIVE_Pos) | \
					(GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
					(GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) | \
					(GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos) 

#define INPUT_CONF (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos) | \
					(GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) | \
					(GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | \
					(GPIO_PIN_CNF_PULL_Pulldown << GPIO_PIN_CNF_PULL_Pos) | \
					(GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)

#define PORT1_PIN_HIGH(pin) (NRF_P1->OUTSET = (1UL << pin))
#define PORT1_PIN_LOW(pin) (NRF_P1->OUTCLR = (1UL << pin))

#define PORT0_PIN_HIGH(pin) (NRF_P0->OUTSET = (1UL << pin))
#define PORT0_PIN_LOW(pin) (NRF_P0->OUTCLR = (1UL << pin))


#define UNSET_CS 		PORT1_PIN_LOW(CS_PIN)
#define SET_CS 	 		PORT1_PIN_HIGH(CS_PIN)

#define UNSET_DCX 		PORT1_PIN_LOW(DCX_PIN)
#define SET_DCX 		PORT1_PIN_HIGH(DCX_PIN)	

#define UNSET_WRX 		PORT1_PIN_LOW(WRX_PIN)
#define SET_WRX 		PORT1_PIN_HIGH(WRX_PIN)

#define UNSET_RDX 		PORT1_PIN_LOW(RDX_PIN)
#define SET_RDX 		PORT1_PIN_HIGH(RDX_PIN)

#define UNSET_TESTPIN NRF_GPIO->OUTCLR = (1UL << TEST_PIN)
#define SET_TESTPIN NRF_GPIO->OUTSET = (1UL << TEST_PIN)	

void delay(void);
void clearParPort(void);
void config_data_pins(void);
void config_gpio_output(uint8_t pin, uint8_t port);
void config_gpio_input(uint8_t pin, uint8_t port);
void remove_config_gpio(uint8_t pin, uint8_t port);
void config_dport_out(void);
void config_dport_in(void);


